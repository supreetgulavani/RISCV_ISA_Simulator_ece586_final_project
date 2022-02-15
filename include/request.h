#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <iostream>
#include <iomanip>

#include "commondefs.h"

// Class for the request queue
class request {
public:
    //program counter and address
    uint64_t program_counter;
    uint64_t address;

    bool busy = false;
    bool valid = false;
    
   //prints program counter and address of the corresponding request
    friend std::ostream& operator<<(std::ostream& os, request &req)
    {
        os << "Program Counter " << std::hex << req.program_counter << " " << "Address: " << std::uppercase << std::hex 
            << req.address << std::endl;

        return os;
    }
    
};

#endif