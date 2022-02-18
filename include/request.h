#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <iostream>
#include <iomanip>

#include "commondefs.h"

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
};

#endif