import React, { useCallback, useMemo } from 'react';
import ReactFlow, {
  Controls,
  Background,
  useNodesState,
  useEdgesState,
  EdgeTypes,
} from 'reactflow';
import 'reactflow/dist/style.css';
import { useValidation } from '../../context/ValidationContext';
import StateNode from './StateNode';
import { Node, Edge, State } from '../../types';

const nodeTypes = {
  stateNode: StateNode,
};

const TuringMachineVisualizer: React.FC = () => {
  const { validationResult, isSimulating } = useValidation();
  
  const currentState = validationResult?.state || 'Start';
  
  // Define initial nodes (states)
  const initialNodes: Node[] = useMemo(() => [
    {
      id: 'Start',
      type: 'stateNode',
      position: { x: 250, y: 50 },
      data: { 
        label: 'Start',
        isActive: currentState === 'Start',
        state: 'Start'
      },
    },
    {
      id: 'CapitalFound',
      type: 'stateNode',
      position: { x: 100, y: 200 },
      data: { 
        label: 'Capital Found',
        isActive: currentState === 'CapitalFound',
        state: 'CapitalFound'
      },
    },
    {
      id: 'DigitFound',
      type: 'stateNode',
      position: { x: 400, y: 200 },
      data: { 
        label: 'Digit Found',
        isActive: currentState === 'DigitFound',
        state: 'DigitFound'
      },
    },
    {
      id: 'CapitalAndDigitFound',
      type: 'stateNode',
      position: { x: 250, y: 350 },
      data: { 
        label: 'Capital & Digit Found',
        isActive: currentState === 'CapitalAndDigitFound',
        state: 'CapitalAndDigitFound'
      },
    },
    {
      id: 'Accept',
      type: 'stateNode',
      position: { x: 100, y: 500 },
      data: { 
        label: 'Accept',
        isActive: currentState === 'Accept',
        state: 'Accept'
      },
    },
    {
      id: 'Reject',
      type: 'stateNode',
      position: { x: 400, y: 500 },
      data: { 
        label: 'Reject',
        isActive: currentState === 'Reject',
        state: 'Reject'
      },
    },
  ], [currentState]);

  const initialEdges: Edge[] = useMemo(() => [
    {
      id: 'start-capital',
      source: 'Start',
      target: 'CapitalFound',
      label: 'A-Z',
      animated: currentState === 'CapitalFound',
    },
    {
      id: 'start-digit',
      source: 'Start',
      target: 'DigitFound',
      label: '0-9',
      animated: currentState === 'DigitFound',
    },
    {
      id: 'capital-both',
      source: 'CapitalFound',
      target: 'CapitalAndDigitFound',
      label: '0-9',
      animated: currentState === 'CapitalAndDigitFound' && validationResult?.hasCapital,
    },
    {
      id: 'digit-both',
      source: 'DigitFound',
      target: 'CapitalAndDigitFound',
      label: 'A-Z',
      animated: currentState === 'CapitalAndDigitFound' && validationResult?.hasDigit,
    },
    {
      id: 'both-accept',
      source: 'CapitalAndDigitFound',
      target: 'Accept',
      label: 'Length ≥ 8',
      animated: currentState === 'Accept',
    },
    {
      id: 'both-reject',
      source: 'CapitalAndDigitFound',
      target: 'Reject',
      label: 'Length < 8',
      animated: currentState === 'Reject' && validationResult?.hasCapital && validationResult?.hasDigit,
    },
    {
      id: 'start-reject',
      source: 'Start',
      target: 'Reject',
      label: 'End of input',
      animated: currentState === 'Reject' && !validationResult?.hasCapital && !validationResult?.hasDigit,
    },
    {
      id: 'capital-reject',
      source: 'CapitalFound',
      target: 'Reject',
      label: 'End of input',
      animated: currentState === 'Reject' && validationResult?.hasCapital && !validationResult?.hasDigit,
    },
    {
      id: 'digit-reject',
      source: 'DigitFound',
      target: 'Reject',
      label: 'End of input',
      animated: currentState === 'Reject' && !validationResult?.hasCapital && validationResult?.hasDigit,
    },
  ], [currentState, validationResult]);

  const [nodes, setNodes, onNodesChange] = useNodesState(initialNodes);
  const [edges, setEdges, onEdgesChange] = useEdgesState(initialEdges);

  // Update nodes when state changes
  React.useEffect(() => {
    setNodes((nds) =>
      nds.map((node) => {
        return {
          ...node,
          data: {
            ...node.data,
            isActive: node.id === currentState,
          },
        };
      })
    );
    
    setEdges((eds) =>
      eds.map((edge) => {
        let animated = false;
        
        // Set animation based on current state and transition conditions
        if (
          (edge.source === 'Start' && edge.target === 'CapitalFound' && currentState === 'CapitalFound') ||
          (edge.source === 'Start' && edge.target === 'DigitFound' && currentState === 'DigitFound') ||
          (edge.source === 'CapitalFound' && edge.target === 'CapitalAndDigitFound' && currentState === 'CapitalAndDigitFound' && validationResult?.hasCapital) ||
          (edge.source === 'DigitFound' && edge.target === 'CapitalAndDigitFound' && currentState === 'CapitalAndDigitFound' && validationResult?.hasDigit) ||
          (edge.source === 'CapitalAndDigitFound' && edge.target === 'Accept' && currentState === 'Accept') ||
          (edge.source === 'CapitalAndDigitFound' && edge.target === 'Reject' && currentState === 'Reject' && validationResult?.hasCapital && validationResult?.hasDigit) ||
          (edge.source === 'Start' && edge.target === 'Reject' && currentState === 'Reject' && !validationResult?.hasCapital && !validationResult?.hasDigit) ||
          (edge.source === 'CapitalFound' && edge.target === 'Reject' && currentState === 'Reject' && validationResult?.hasCapital && !validationResult?.hasDigit) ||
          (edge.source === 'DigitFound' && edge.target === 'Reject' && currentState === 'Reject' && !validationResult?.hasCapital && validationResult?.hasDigit)
        ) {
          animated = true;
        }
        
        return {
          ...edge,
          animated,
        };
      })
    );
  }, [currentState, setNodes, setEdges, validationResult]);

  const proOptions = { hideAttribution: true };

  return (
    <div className="h-[500px] w-full bg-white rounded-lg shadow-md">
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        nodeTypes={nodeTypes}
        fitView
        proOptions={proOptions}
      >
        <Controls />
        <Background />
      </ReactFlow>
      
      {validationResult && isSimulating && validationResult.tape && (
        <div className="bg-gray-100 p-4 mt-4 rounded-b-lg border-t border-gray-300">
          <h3 className="text-lg font-medium mb-2">Turing Machine Tape</h3>
          <div className="flex justify-center items-center space-x-1 font-mono overflow-x-auto py-2">
            {validationResult.tape.split('').map((char, idx) => (
              <div 
                key={idx}
                className={`w-10 h-10 flex items-center justify-center border ${
                  idx === validationResult.currentPosition ? 'bg-blue-500 text-white border-blue-700' : 'bg-white border-gray-300'
                }`}
              >
                {char === '_' ? '□' : char}
              </div>
            ))}
          </div>
          <div className="text-center mt-2">
            <div className="font-medium">Current State: <span className="text-blue-600">{currentState}</span></div>
            <div>Position: {validationResult.currentPosition}</div>
          </div>
        </div>
      )}
    </div>
  );
};

export default TuringMachineVisualizer;