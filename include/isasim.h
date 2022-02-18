#ifndef __ISASIM_H__
#define __ISASIM_H__

// just a file to initiate PC and SP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "request.h"

// ISA SIMULATOR CLASS ...only class. B)
class isa_sim{
    public:
    uint64_t program_counter;
    uint64_t stack_pointer;

    //Print memory image
    void print_mem(){
        int mem_elements = 0;
        //100 elements only for now.
        //simulation too slow with 64k.
        for (int i = mem_elements; i <= 100; i++){
            std::cout << i << ":" << std::uppercase << std::hex << (int)memory_array[i] << "\t";
        }
    }


};

#endif

