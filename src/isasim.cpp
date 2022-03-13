#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"

#ifdef STEP
char step;
char mem_step;
#endif

isa_sim::isa_sim(std::ofstream &isa_reg):
    isa_reg_file(isa_reg)
{
        program_counter = 0;
        stack_pointer = 65536;
}


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
    /////////////////////////////////////////////////
    /////   CORRECT?    /////////////////////////////
    uint64_t current_sp = stack_pointer;
    /////////////////////////////////////////////////
    while (1){
        #ifdef STEP 
            std::cout << "\nDo you want to step?(y/n)" << "\n" <<std::endl;
            std::cin >> step;
        #endif
        current_instr current(current_pc, current_sp, isa_reg_file);
        current.instr_execution(r);
        //update the pc and sp here
        /*#ifdef STEP
        std::cout << "Do you want mem?(y/n)" << "\n" << std::endl;
        std::cin >> mem_step;
        if (mem_step)
            print_mem();
        #endif*/
        if ((current.c_instr == 0x00008067) && (r[0x1] == 0x0))
            break;
    }
    if (debug){
        
        std::stringstream op;
        op << "Register values are:" << std::endl;
        int reg_elements = 0;
        for (int i = reg_elements; i <= 31; i++){
            op << i << ":" << std::uppercase << std::hex << r[i] << "\t";
        }
    op << "\nProgram Counter:" << std:: uppercase << std::hex << current_pc << "\n" << std::endl;
    std::cout << op.str();
    isa_reg_file << op.str();

    }
}
