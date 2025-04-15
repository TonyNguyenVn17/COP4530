// Thien Minh Nguyen U11796783

#ifndef GRITVM_H
#define GRITVM_H

#include "GritVMBase.hpp"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class GritVM : public GritVMInterface {
private:
    // Memory 
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator currentInstruct;
    
    // Machine 
    STATUS machineStatus;
    long accumulator;

    // Helper methods 
    long evaluate(const Instruction& instruction);
    void advance(long jumpDistance);
    bool checkMemoryBounds(long index) const;  
    
    // Helper for arithmetic operations
    void performConstOperation(const Instruction& instruction);
    void performMemoryOperation(const Instruction& instruction);
    void performJumpOperation(const Instruction& instruction, long& jumpDistance);

public:
    GritVM();
    ~GritVM();

    STATUS load(const std::string filename, const std::vector<long> &initialMemory) override;
    STATUS run() override;
    std::vector<long> getDataMem() override;  // Removed const since it's not in base class
    STATUS reset() override;
    
    // Additional utility method
    void printVM(bool printData = true, bool printInstruction = true) const;  // Made const
};

#endif /* GRITVM_H */