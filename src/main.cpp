#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"
#include "request.h"  

bool verbose;
bool debug;

int main(int argc, char *argv[])
{
    // Input Trace File
    std::string ip_mem_name;
    std::ifstream *ip_mem_fstream;
    std::string ip_string;

    // Output MEM commands file
    std::ofstream mem_fstream;
    std::string op_fname;

    
    // Check if input trace file is provided
    // First argument is always executable name
    if (argc < 7) {
        std::cerr << "Wrong command..\n\n";
        std::cerr << "Usage: ./ece586_isa_simulator <input_mem_file> <output_mem_file> <program_counter> <stack_address> <verbose_mode> <debug_mode>" << std::endl;
        return 1;
    }

    // Read the input file name
    ip_mem_name = argv[1];
    std::cout << "Input file: " << ip_mem_name << std::endl;

    // Check if the file opens
    ip_mem_fstream = new std::ifstream(ip_mem_name);
    if (!ip_mem_fstream->is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Open output file with argument name
    op_fname = argv[2];
    std::cout << "Output File: " << op_fname << std::endl;
    mem_fstream.open(op_fname, std::ios::out);

    isa_sim isa(mem_fstream);
        
    // Take Program Counter as input
    isa.program_counter = std::strtoul(argv[3], nullptr, 16);
    std::cout << "Program Counter: " << std::uppercase << std::hex << isa.program_counter << std::endl;

    // Take Stack Address as input
    isa.stack_address = std::strtoul(argv[4], nullptr, 16);
    std::cout << "Stack Address: " << std::uppercase << std::hex << isa.stack_address << std::endl;

    // Verbose Mode (Needed for demo)
    verbose = atoi(argv[5]);
    
    // Debug Mode (Extra prints for development)
    debug = atoi(argv[6]);

    std::cout << "Verbose Mode: " << verbose << " Debug Mode: " << debug << std::endl;
    
    //output Stack Pointer
    std::cout << "Stack Pointer: " << std::uppercase << std::hex << isa.stack_pointer << std::endl;

    //Output Return Address
    std::cout << "Return Address: " << std::uppercase << std::hex << isa.return_addr << std::endl;

    request req; 
    
    // Print starting message
    std::cout << "\n -- Starting Simulation -- \n" << std::endl;

 
    while (true) {
        // Check if we can read in a request
        if ((ip_mem_fstream->is_open())) {
            // Read a new line
            ip_string = "";
            //req.instruction_location =  req.instruction_location + 4;
            while (ip_string.empty() && ip_mem_fstream->is_open()) {
                std::getline(*ip_mem_fstream,ip_string);
                // File over?
                 if (ip_mem_fstream->eof()) {
                    ip_mem_fstream->close();
                    break;
                }
            }
            read_file(ip_string, req);
            #ifdef DEBUG 
            std::cout  << req << std::endl;
            #endif
        }
        
          if (!(ip_mem_fstream->is_open())) {
            #ifdef DEBUG
            std::cout << "\n -- Input file Over! -- \n" << std::endl;
            #endif
            break;
          }
          
    }

    // Free the filestream heap
    delete ip_mem_fstream;
    
    #ifdef DEBUG
    if (debug || verbose){
    //print mem image
    std::cout << "\n----------- Memory --------------" << std::endl;
    isa.print_mem();
    std::cout << "\n--------- End Memory ------------" << std::endl;
    }
    #endif

    #ifdef BREAK
    // Ask for breakpoints
    ask_bp:
    int64_t bp;
    std::cout << "Enter PC for breakpoint. Enter -1 to skip and start execution: ";
    std::cin >> bp;
    if (bp != -1) {
      isa.set_breakpoint(bp);
      goto ask_bp;
    }
    #endif

    isa.start_execution();
    std::cout << "\n" << std::endl;
      // Close output file
    mem_fstream.close();
    std::cout << "\n -- Ending Simulation -- \n" << std::endl;
    return 0;

}
