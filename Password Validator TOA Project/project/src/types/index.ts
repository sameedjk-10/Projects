export type State = 
  | 'Start'
  | 'CapitalFound'
  | 'DigitFound'
  | 'CapitalAndDigitFound'
  | 'Accept'
  | 'Reject';

export interface ValidationResult {
  state: State;
  length: number;
  hasCapital: boolean;
  hasDigit: boolean;
  currentPosition?: number;
  currentChar?: string;
  tape?: string;
}

export interface Node {
  id: string;
  type: string;
  position: {
    x: number;
    y: number;
  };
  data: {
    label: string;
    isActive: boolean;
  };
}

export interface Edge {
  id: string;
  source: string;
  target: string;
  label: string;
  animated?: boolean;
}