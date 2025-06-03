import React from 'react';
import { useState } from 'react';
import { ChevronDown, ChevronUp } from 'lucide-react';

const TuringExplanation: React.FC = () => {
  const [isOpen, setIsOpen] = useState(false);
  
  return (
    <div className="bg-white rounded-lg shadow-md p-6 w-full">
      <div 
        className="flex justify-between items-center cursor-pointer"
        onClick={() => setIsOpen(!isOpen)}
      >
        <h2 className="text-xl font-bold">What is a Turing Machine?</h2>
        <button className="text-gray-500 hover:text-gray-700">
          {isOpen ? <ChevronUp size={24} /> : <ChevronDown size={24} />}
        </button>
      </div>
      
      {isOpen && (
        <div className="mt-4 space-y-4">
          <p>
            A Turing machine is a mathematical model of computation that defines an abstract machine, which manipulates symbols on a strip of tape according to a table of rules. Despite the model's simplicity, it can be adapted to simulate the logic of any computer algorithm.
          </p>
          
          <h3 className="text-lg font-semibold mt-2">Components of our Password Validator Turing Machine:</h3>
          
          <div className="ml-4">
            <h4 className="font-medium">States:</h4>
            <ul className="list-disc ml-6">
              <li><span className="font-medium text-blue-600">Start:</span> Initial state</li>
              <li><span className="font-medium text-yellow-600">CapitalFound:</span> Found at least one uppercase letter</li>
              <li><span className="font-medium text-yellow-600">DigitFound:</span> Found at least one digit</li>
              <li><span className="font-medium text-purple-600">CapitalAndDigitFound:</span> Found both an uppercase letter and a digit</li>
              <li><span className="font-medium text-green-600">Accept:</span> Password meets all requirements</li>
              <li><span className="font-medium text-red-600">Reject:</span> Password does not meet all requirements</li>
            </ul>
            
            <h4 className="font-medium mt-3">Transitions:</h4>
            <ul className="list-disc ml-6">
              <li>When an uppercase letter is read, move from Start → CapitalFound</li>
              <li>When a digit is read, move from Start → DigitFound</li>
              <li>When a digit is read in CapitalFound state, move to CapitalAndDigitFound</li>
              <li>When an uppercase letter is read in DigitFound state, move to CapitalAndDigitFound</li>
              <li>At the end of input, if in CapitalAndDigitFound state and length ≥ 8, move to Accept</li>
              <li>Otherwise, move to Reject</li>
            </ul>
          </div>
          
          <p className="text-sm bg-gray-100 p-3 rounded">
            <strong>Note:</strong> The visualization above simulates how a Turing machine would process your password character by character, transitioning between states based on the input. The animated edges show the active transition path as the validation progresses.
          </p>
        </div>
      )}
    </div>
  );
};

export default TuringExplanation;