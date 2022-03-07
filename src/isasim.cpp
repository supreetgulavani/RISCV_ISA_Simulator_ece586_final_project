#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"

void isa_sim::print_mem(){
    int mem_elements = 0;
    //100 elements only for now.
    //simulation too slow with 64k.
    for (int i = mem_elements; i <= 100; i++){
        std::cout << i << ":" << std::uppercase << std::hex << (int)memory_array[i] << "\t";
    }
}


void isa_sim::start_execution(){

    uint64_t current_pc = program_counter;
    uint64_t current_sp = stack_pointer;
    while (1){
        current_instr current(current_pc, current_sp);
        current.instr_execution(r);
        //update the pc and sp here
        if ((current.c_instr == 0x00008067) && (r[0x1] == 0x0))
            break;
        
        current_pc = current_pc + 4;
    }
}