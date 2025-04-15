// Thien Minh Nguyen U11796783

#include "GritVM.hpp"

GritVM::GritVM() {
    reset(); 
}

GritVM::~GritVM() {
}

STATUS GritVM::reset() {
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    machineStatus = WAITING;
    return machineStatus;
}

// Load a program into the VM and start checking for errors
STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory) {
    if (machineStatus != WAITING) {
        return machineStatus;
    }
    
    instructMem.clear();
    dataMem = initialMemory; 
    
    // Open the file to reads and parse correct instructions
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        Instruction instr = GVMHelper::parseInstruction(line);
        
        if (instr.operation == UNKNOWN_INSTRUCTION) {
            machineStatus = ERRORED;
            return machineStatus;
        }
        
        instructMem.push_back(instr);
    }
    
    // Set the status based on whether we have instructions
    if (instructMem.empty()) {
        machineStatus = WAITING;
    } else {
        machineStatus = READY;
        currentInstruct = instructMem.begin();
    }
    
    return machineStatus;
}

// Execute the loaded program
STATUS GritVM::run() {
    if (machineStatus != READY) {
        return machineStatus;
    }
    
    machineStatus = RUNNING;
    currentInstruct = instructMem.begin();
    
    while (machineStatus == RUNNING) {
        long jumpDistance = evaluate(*currentInstruct);
        
        advance(jumpDistance);
    }
    
    return machineStatus;
}

// Get a copy of the data memory
std::vector<long> GritVM::getDataMem() {
    return dataMem;
}

// Check for valid memory access
bool GritVM::checkMemoryBounds(long index) const {
    if (index < 0 || index >= static_cast<long>(dataMem.size())) {
        return false;
    }
    return true;
}

// Perform operations with a constant
void GritVM::performConstOperation(const Instruction& instruction) {
    switch (instruction.operation) {
        case ADDCONST:
            accumulator += instruction.argument;
            break;
        case SUBCONST:
            accumulator -= instruction.argument;
            break;
        case MULCONST:
            accumulator *= instruction.argument;
            break;
        case DIVCONST:
            if (instruction.argument == 0) {
                machineStatus = ERRORED;
            } else {
                accumulator /= instruction.argument;
            }
            break;
        default:
            break;
    }
}

// Perform operations with memory
void GritVM::performMemoryOperation(const Instruction& instruction) {
    if (!checkMemoryBounds(instruction.argument)) {
        machineStatus = ERRORED;
        return;
    }

    switch (instruction.operation) {
        case ADDMEM:
            accumulator += dataMem[instruction.argument];
            break;
        case SUBMEM:
            accumulator -= dataMem[instruction.argument];
            break;
        case MULMEM:
            accumulator *= dataMem[instruction.argument];
            break;
        case DIVMEM:
            if (dataMem[instruction.argument] == 0) {
                machineStatus = ERRORED;
            } else {
                accumulator /= dataMem[instruction.argument];
            }
            break;
        default:
            break;
    }
}

// Perform jump operations
void GritVM::performJumpOperation(const Instruction& instruction, long& jumpDistance) {
    if (instruction.argument == 0) {
        machineStatus = ERRORED;
        jumpDistance = 0;
        return;
    }

    switch (instruction.operation) {
        case JUMPREL:
            jumpDistance = instruction.argument;
            break;
        case JUMPZERO:
            if (accumulator == 0) {
                jumpDistance = instruction.argument;
            }
            break;
        case JUMPNZERO:
            if (accumulator != 0) {
                jumpDistance = instruction.argument;
            }
            break;
        default:
            break;
    }
}

// Evaluate a single instruction and return the jump distance
long GritVM::evaluate(const Instruction& instruction) {
    long jumpDistance = 1;
    
    switch (instruction.operation) {
        case CLEAR:
            accumulator = 0;
            break;
            
        case AT:
            if (checkMemoryBounds(instruction.argument)) {
                accumulator = dataMem[instruction.argument];
            } else {
                machineStatus = ERRORED;
            }
            break;
            
        case SET:
            if (checkMemoryBounds(instruction.argument)) {
                dataMem[instruction.argument] = accumulator;
            } else {
                machineStatus = ERRORED;
            }
            break;
            
        case INSERT:
            if (instruction.argument >= 0 && instruction.argument <= static_cast<long>(dataMem.size())) {
                dataMem.insert(dataMem.begin() + instruction.argument, accumulator);
            } else {
                machineStatus = ERRORED;
            }
            break;
            
        case ERASE:
            if (checkMemoryBounds(instruction.argument)) {
                dataMem.erase(dataMem.begin() + instruction.argument);
            } else {
                machineStatus = ERRORED;
            }
            break;
            
        // Accumulator Maths with a constant
        case ADDCONST:
        case SUBCONST:
        case MULCONST:
        case DIVCONST:
            performConstOperation(instruction);
            break;
            
        // Accumulator Maths with a memory location
        case ADDMEM:
        case SUBMEM:
        case MULMEM:
        case DIVMEM:
            performMemoryOperation(instruction);
            break;
            
        // Instruction Jump Functions
        case JUMPREL:
        case JUMPZERO:
        case JUMPNZERO:
            performJumpOperation(instruction, jumpDistance);
            break;
            
        // Misc Functions
        case NOOP:
            // Do nothing
            break;
            
        case HALT:
            machineStatus = HALTED;
            break;
            
        case OUTPUT:
            std::cout << accumulator << std::endl;
            break;
            
        case CHECKMEM:
            if (dataMem.size() < static_cast<unsigned long>(instruction.argument)) {
                machineStatus = ERRORED;
            }
            break;
            
        case UNKNOWN_INSTRUCTION:
        default:
            machineStatus = ERRORED;
            break;
    }
    
    return jumpDistance;
}

// Advance the instruction pointer by the specified distance
void GritVM::advance(long jumpDistance) {
    // If the machine is not running, don't advance
    if (machineStatus != RUNNING) {
        return;
    }
    
    // Move the instruction pointer by jumpDistance
    for (long i = 0; i < std::abs(jumpDistance); i++) {
        if (jumpDistance > 0) {
            currentInstruct++;
        } else {
            currentInstruct--;
        }
        
        // Check if we've reached the end of instructions
        if (currentInstruct == instructMem.end()) {
            machineStatus = HALTED;
            return;
        }
        
        // Check if we've gone past the beginning of instructions
        if (jumpDistance < 0 && currentInstruct == instructMem.begin() && i < std::abs(jumpDistance) - 1) {
            machineStatus = ERRORED;
            return;
        }
    }
}

// Utility method to print VM state
void GritVM::printVM(bool printData, bool printInstruction) const {
    std::cout << "****** Output Dump ******" << std::endl;
    std::cout << "Status: " << GVMHelper::statusToString(machineStatus) << std::endl;
    std::cout << "Accumulator: " << accumulator << std::endl;
    
    if (printData) {
        std::cout << "*** Data Memory ***" << std::endl;
        int index = 0;
        for (const auto& item : dataMem) {
            std::cout << "Location " << index++ << ": " << item << std::endl;
        }
    }
    
    if (printInstruction) {
        std::cout << "*** Instruction Memory ***" << std::endl;
        int index = 0;
        for (const auto& item : instructMem) {
            std::cout << "Instruction " << index++ << ": " << 
                GVMHelper::instructionToString(item.operation) << 
                " " << item.argument << std::endl;
        }
    }
}