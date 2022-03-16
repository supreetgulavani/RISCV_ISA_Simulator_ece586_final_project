#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"

#ifdef STEP
char step = 'y';
#endif


std::list <int64_t> mylist;

isa_sim::isa_sim(std::ofstream &isa_reg):
    isa_reg_file(isa_reg)
{
        program_counter = 0;
        stack_pointer = 0;
}


void isa_sim::print_mem(){
    int mem_elements = 0;
    //100 elements only for now.
    //simulation too slow with 64k.
    for (int i = mem_elements; i <= 100; i++){
        std::cout << i << ":" << std::uppercase << std::hex << (int)memory_array[i] << "\t";
    }
}

#ifdef BREAK
void isa_sim::set_breakpoint(uint64_t pc)
{
    breakpoints.push_back(pc);
}

bool isa_sim::is_breakpoint(uint64_t pc)
{
    return (std::find(breakpoints.begin(), breakpoints.end(), pc) != breakpoints.end());
}
#endif

void isa_sim::start_execution(){

    uint32_t current_pc = program_counter;
    uint64_t current_sp = (uint32_t)stack_address + 1;
    while (1){
        mylist.push_back(current_pc);
        #ifdef STEP
        if (step == 'Y' || step == 'y') {
            std::cout << "\nDo you want to step?(y/n)" << "\n" <<std::endl;
            scanf("%c", &step);
            getchar();
        }
        #endif
        #ifdef BREAK
        if (is_breakpoint(current_pc)) {
            std::cout << "\nBreakpoint at " << current_pc << " . Press any key to continue.\n" << std::endl;
            std:: stringstream op;
            op << "Register values are:" << std::endl;
            int reg_elements = 0;
            for (int i = reg_elements; i <= 31; i++){
                op << i << ":" << std::uppercase << std::hex << r[i] << "\t";
            }
            op << "\nProgram Counter:" << std:: uppercase << std::hex << current_pc << "\n" << std::endl;
            std::cout << op.str();

            // Accept any key
            char c;
            scanf("%c", &c);
            getchar();
        }
        #endif
        current_instr current(current_pc, current_sp, isa_reg_file);
        current.instr_execution(r);
        if (((current.c_instr == 0x00008067) && (r[0x1] == 0x0)) | (current.c_instr == 0x00000000))

        break;
    }
    if (debug){
        
        std::stringstream op;
        op << "Register values are:" << std::endl;
        int reg_elements = 0;
        for (int i = reg_elements; i <= 31; i++){
            op << i << ":" << std::uppercase << std::hex << r[i] << "\t";
        }
    op << "\nProgram Counter:" << *std::prev(mylist.end()) << '\n';
    std::cout << op.str();
    isa_reg_file << op.str();

    }
}
