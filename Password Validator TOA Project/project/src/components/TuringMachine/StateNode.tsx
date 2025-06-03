import React, { memo } from 'react';
import { Handle, Position } from 'reactflow';
import { State } from '../../types';

interface StateNodeProps {
  data: {
    label: string;
    isActive: boolean;
    state: State;
  };
}

const getStateColor = (state: State, isActive: boolean) => {
  if (!isActive) return 'bg-gray-200 text-gray-700 border-gray-400';
  
  switch (state) {
    case 'Start':
      return 'bg-blue-100 text-blue-800 border-blue-500';
    case 'CapitalFound':
    case 'DigitFound':
      return 'bg-yellow-100 text-yellow-800 border-yellow-500';
    case 'CapitalAndDigitFound':
      return 'bg-purple-100 text-purple-800 border-purple-500';
    case 'Accept':
      return 'bg-green-100 text-green-800 border-green-500';
    case 'Reject':
      return 'bg-red-100 text-red-800 border-red-500';
    default:
      return 'bg-gray-200 text-gray-700 border-gray-400';
  }
};

const StateNode = memo(({ data }: StateNodeProps) => {
  const stateColor = getStateColor(data.state as State, data.isActive);
  
  return (
    <div className={`px-4 py-2 rounded-lg border-2 ${stateColor} ${data.isActive ? 'shadow-md transform scale-110 transition-transform duration-300' : 'opacity-80'}`}>
      <Handle type="target" position={Position.Top} className="w-3 h-3 bg-gray-400" />
      <div className="font-medium text-center">{data.label}</div>
      <Handle type="source" position={Position.Bottom} className="w-3 h-3 bg-gray-400" />
    </div>
  );
});

export default StateNode;