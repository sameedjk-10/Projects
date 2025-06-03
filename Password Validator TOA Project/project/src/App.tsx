import React from 'react';
import { ValidationProvider } from './context/ValidationContext';
import Header from './components/Header/Header';
import PasswordForm from './components/PasswordForm/PasswordForm';
import TuringMachineVisualizer from './components/TuringMachine/TuringMachineVisualizer';
import TuringExplanation from './components/Explanation/TuringExplanation';
import './App.css';

function App() {
  return (
    <ValidationProvider>
      <div className="min-h-screen bg-gray-100">
        <Header />
        
        <main className="container mx-auto py-8 px-4">
          <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
            <div className="flex flex-col gap-6">
              <PasswordForm />
              <TuringExplanation />
            </div>
            
            <div className="flex flex-col gap-4">
              <h2 className="text-xl font-bold">Turing Machine Visualization</h2>
              <p className="text-gray-600 mb-2">
                This visualization shows how a Turing machine processes your password, 
                transitioning between states based on the characters it reads.
              </p>
              <TuringMachineVisualizer />
            </div>
          </div>
        </main>
        
        <footer className="bg-gray-800 text-white py-4 mt-12">
          <div className="container mx-auto text-center">
            <p>Turing Machine Password Validator © 2025</p>
          </div>
        </footer>
      </div>
    </ValidationProvider>
  );
}

export default App;