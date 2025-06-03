import React, { createContext, useContext, useState, ReactNode } from 'react';
import { ValidationResult, State } from '../types';
import { simulateTuringMachine } from '../utils/simulateTuringMachine';

interface ValidationContextType {
  password: string;
  setPassword: (password: string) => void;
  validationResult: ValidationResult | null;
  simulationStep: number;
  setSimulationStep: (step: number) => void;
  isSimulating: boolean;
  setIsSimulating: (isSimulating: boolean) => void;
  validatePassword: () => void;
  simulateStep: () => void;
  resetSimulation: () => void;
  loading: boolean;
  error: string | null;
}

const ValidationContext = createContext<ValidationContextType | undefined>(undefined);

export const ValidationProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
  const [password, setPassword] = useState('');
  const [validationResult, setValidationResult] = useState<ValidationResult | null>(null);
  const [simulationStep, setSimulationStep] = useState(-1);
  const [isSimulating, setIsSimulating] = useState(false);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const validatePassword = async () => {
    setLoading(true);
    setError(null);

    try {
      // For this frontend-only version, we'll simulate the API call
      const result = simulateTuringMachine(password, -1);
      setValidationResult(result);
    } catch (err) {
      setError('Failed to validate password. Please try again.');
      console.error(err);
    } finally {
      setLoading(false);
    }
  };

  const simulateStep = () => {
    if (!password) return;
    
    const nextStep = simulationStep + 1;
    
    // If we're at the end of the password plus the ending blank
    if (nextStep > password.length + 1) {
      return;
    }
    
    const stepResult = simulateTuringMachine(password, nextStep);
    setValidationResult(stepResult);
    setSimulationStep(nextStep);
  };

  const resetSimulation = () => {
    setSimulationStep(-1);
    setValidationResult(null);
    setIsSimulating(false);
  };

  return (
    <ValidationContext.Provider
      value={{
        password,
        setPassword,
        validationResult,
        simulationStep,
        setSimulationStep,
        isSimulating,
        setIsSimulating,
        validatePassword,
        simulateStep,
        resetSimulation,
        loading,
        error
      }}
    >
      {children}
    </ValidationContext.Provider>
  );
};

export const useValidation = () => {
  const context = useContext(ValidationContext);
  if (context === undefined) {
    throw new Error('useValidation must be used within a ValidationProvider');
  }
  return context;
};