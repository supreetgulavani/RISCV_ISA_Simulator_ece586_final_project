#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <iostream>
#include <iomanip>

#include "commondefs.h"
#include "memory.h"

// Class for the request queue
class request {
public:
    //Instruction Location, instruction
    uint64_t instruction_location;
    uint64_t instruction;
    
    //uint64_t program_counter;
    bool busy = false;
    bool valid = false;

   //prints instruction of the corresponding request
    friend std::ostream& operator<<(std::ostream& os, request &req)
    {
        os << "\nInstruction Location: " << std::uppercase << std::hex << req.instruction_location << "  " << "Instruction: " << std::uppercase << std::hex 
            << req.instruction << "\n"  << std::endl;
        return os;
    }
    
    //loading memory with program instr

    void load_mem(request &req){

        memory_array[req.instruction_location]     = (req.instruction & (0x000000FF));
        memory_array[req.instruction_location + 1] = ((req.instruction & (0x0000FF00)) >> 8);
        memory_array[req.instruction_location + 2] = ((req.instruction & (0x00FF0000)) >> 16);
        memory_array[req.instruction_location + 3] = ((req.instruction & (0xFF000000)) >> 24);
    }

};

#endif