import { State, ValidationResult } from '../types';

/**
 * Simulates the Turing machine for password validation
 * @param password - The password to validate
 * @param currentPosition - Current position of the head (for step-by-step simulation)
 * @returns ValidationResult object
 */
export const simulateTuringMachine = (
  password: string,
  currentPosition: number = -1
): ValidationResult => {
  // Simulate tape by adding blanks '_' at start and end
  const tape = '_' + password + '_';
  let head = currentPosition === -1 ? tape.length - 1 : currentPosition + 1;
  let currentState: State = 'Start';
  
  // Track requirements separately
  let hasCapital = false;
  let hasDigit = false;
  
  // Process all characters in the password to check requirements
  for (let i = 1; i < tape.length - 1; i++) {
    const char = tape[i];
    if (/[A-Z]/.test(char)) {
      hasCapital = true;
    }
    if (/[0-9]/.test(char)) {
      hasDigit = true;
    }
  }

  // For step-by-step simulation, only process up to current head position
  if (currentPosition !== -1) {
    hasCapital = false;
    hasDigit = false;
    for (let i = 1; i <= head && i < tape.length - 1; i++) {
      const char = tape[i];
      if (/[A-Z]/.test(char)) {
        hasCapital = true;
      }
      if (/[0-9]/.test(char)) {
        hasDigit = true;
      }
    }
  }

  // Determine current state based on requirements met
  if (hasCapital && hasDigit) {
    currentState = 'CapitalAndDigitFound';
  } else if (hasCapital) {
    currentState = 'CapitalFound';
  } else if (hasDigit) {
    currentState = 'DigitFound';
  }

  // For final state determination
  if (head >= tape.length - 1) {
    if (hasCapital && hasDigit && password.length >= 8) {
      currentState = 'Accept';
    } else {
      currentState = 'Reject';
    }
  }

  return {
    state: currentState,
    length: password.length,
    hasCapital,
    hasDigit,
    currentPosition: head,
    currentChar: head < tape.length ? tape[head] : '_',
    tape
  };
};