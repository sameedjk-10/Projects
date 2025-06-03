import React from 'react';
import { useValidation } from '../../context/ValidationContext';
import { ArrowRight, Check, X } from 'lucide-react';

const PasswordForm: React.FC = () => {
  const { 
    password, 
    setPassword, 
    validationResult, 
    validatePassword, 
    simulateStep,
    isSimulating,
    setIsSimulating,
    resetSimulation,
    loading, 
    error 
  } = useValidation();

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newPassword = e.target.value;
    setPassword(newPassword);
    if (newPassword === '') {
      resetSimulation();
    }
    validatePassword(); // Validate immediately on input change
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    validatePassword();
  };

  const handleStartSimulation = () => {
    resetSimulation();
    setIsSimulating(true);
    simulateStep();
  };

  const validationCriteria = [
    { 
      id: 'length', 
      label: 'At least 8 characters', 
      met: validationResult ? validationResult.length >= 8 : false 
    },
    { 
      id: 'uppercase', 
      label: 'At least one uppercase letter', 
      met: validationResult ? validationResult.hasCapital : false 
    },
    { 
      id: 'digit', 
      label: 'At least one digit', 
      met: validationResult ? validationResult.hasDigit : false 
    }
  ];

  const getStatusMessage = () => {
    if (!password) return '';
    if (validationResult?.state === 'Accept') {
      return 'Password Accepted! ✓';
    }
    return 'Password Requirements Not Met ✗';
  };

  return (
    <div className="bg-white rounded-lg shadow-md p-6 w-full max-w-md">
      <h2 className="text-xl font-bold mb-4">Password Validator</h2>
      
      <form onSubmit={handleSubmit} className="mb-6">
        <div className="mb-4">
          <label 
            htmlFor="password" 
            className="block text-sm font-medium text-gray-700 mb-1"
          >
            Enter Password
          </label>
          <input
            type="text"
            id="password"
            value={password}
            onChange={handleInputChange}
            className="w-full px-4 py-2 rounded-md border border-gray-300 focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent"
            placeholder="Enter password"
            required
          />
        </div>
        
        <div className="flex flex-col sm:flex-row gap-2">
          <button
            type="button"
            onClick={handleStartSimulation}
            disabled={!password || loading}
            className="px-4 py-2 bg-purple-600 text-white rounded-md disabled:bg-purple-300 hover:bg-purple-700 transition-colors flex-1"
          >
            Simulate Step-by-Step
          </button>
        </div>
      </form>
      
      {isSimulating && (
        <div className="mb-6">
          <div className="flex justify-between mb-2">
            <h3 className="text-md font-medium">Step-by-Step Simulation</h3>
            <button 
              onClick={simulateStep}
              className="px-3 py-1 bg-green-600 text-white rounded-md hover:bg-green-700 transition-colors flex items-center gap-1 text-sm"
            >
              Next Step <ArrowRight size={16} />
            </button>
          </div>
          <div className="text-sm text-gray-600 italic mb-2">
            Current character: <span className="font-mono font-bold">
              {validationResult?.currentChar === '_' ? '□' : validationResult?.currentChar || ''}
            </span>
          </div>
        </div>
      )}

      {error && <p className="text-red-600 mb-4">{error}</p>}
      
      <div className="space-y-2 mb-4">
        <h3 className="text-md font-medium">Password Requirements:</h3>
        {validationCriteria.map((criterion) => (
          <div 
            key={criterion.id}
            className="flex items-center gap-2"
          >
            {criterion.met ? (
              <Check size={16} className="text-green-500" />
            ) : (
              <X size={16} className="text-red-500" />
            )}
            <span className={criterion.met ? 'text-green-700' : 'text-gray-700'}>
              {criterion.label}
            </span>
          </div>
        ))}
      </div>

      {password && (
        <div className={`p-3 rounded-md ${
          validationResult?.state === 'Accept' 
            ? 'bg-green-100 text-green-800' 
            : 'bg-red-100 text-red-800'
        }`}>
          <p className="font-medium text-center">{getStatusMessage()}</p>
        </div>
      )}
    </div>
  );
};

export default PasswordForm;