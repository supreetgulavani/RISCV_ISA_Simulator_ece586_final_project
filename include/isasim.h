#ifndef __ISASIM_H__
#define __ISASIM_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include "commondefs.h"
#include "fileparse.h"
#include "request.h"

// ISA SIMULATOR CLASS ...only class. B)
class isa_sim{
    public:
    uint64_t program_counter;
    uint64_t stack_address;
    uint64_t stack_pointer = 65536;
    uint64_t return_addr = 0;

    //Register declaration
    const uint32_t r0 = 0x0;
    uint32_t r [32] = {0};

    //setup pc and sp for current_instr and start execution
    void start_execution();

    //Print memory image
    void print_mem();

    std::ofstream& isa_reg_file;
    
    isa_sim(std::ofstream& isa_reg_file);


};


#endif