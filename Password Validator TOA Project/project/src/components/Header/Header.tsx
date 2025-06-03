import React from 'react';
import { Cpu } from 'lucide-react';

const Header: React.FC = () => {
  return (
    <header className="bg-gradient-to-r from-purple-700 to-blue-700 text-white py-6 px-4 md:px-8">
      <div className="container mx-auto">
        <div className="flex items-center justify-center md:justify-start gap-3">
          <Cpu size={32} className="text-white" />
          <div>
            <h1 className="text-2xl font-bold">Turing Machine Password Validator</h1>
            <p className="text-purple-200">Visualizing state transitions in computational theory</p>
          </div>
        </div>
      </div>
    </header>
  );
};

export default Header;