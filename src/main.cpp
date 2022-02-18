#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"

int main(int argc, char *argv[])
{
    // Input Trace File
    std::string ip_mem_name;
    std::ifstream *ip_mem_fstream;
    std::string ip_string;

    // Output MEM commands file
    std::ofstream mem_fstream;
    std::string op_fname;

    isa_sim isa;

    // Check if input trace file is provided
    // First argument is always executable name
    if (argc < 5) {
        std::cerr << "Wrong command..\n\n";
        std::cerr << "Usage: ./ece586_isa_simulator <input_mem_file> <output_mem_file> <program_counter> <stack_pointer>" << std::endl;
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

    // Take Program Counter as input
    isa.program_counter = std::strtoul(argv[3], nullptr, 16);
    std::cout << "Program Counter: " << std::uppercase << std::hex << isa.program_counter << std::endl;

    // Take Stack Pointer as input
    isa.stack_pointer = std::strtoul(argv[4], nullptr, 16);
    std::cout << "Stack Pointer: " << std::uppercase << std::hex << isa.stack_pointer << std::endl;
 
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

            std::cout  << req << std::endl;
            std::stringstream op;
    
            op  << req.instruction_location << " " << std::hex << req.instruction << " "<< std::uppercase << std::hex << isa.program_counter 
                << std::uppercase << std::hex << " " << isa.stack_pointer << std::endl;
            //std::cout << op.str();
            // Add the parsed contents to a file  (showoff nothing else)
            mem_fstream << op.str();
        }
          if (!(ip_mem_fstream->is_open())) {
            std::cout << "\n -- Input file Over! -- \n" << std::endl;
            break;
          }
    }
    // Free the filestream heap
    delete ip_mem_fstream;

    // Close output file
    mem_fstream.close();
    
    //print mem image
    std::cout << "\n-----------Memory--------------" << std::endl;
    isa.print_mem();
    std::cout << "\n---------End Memory------------" << std::endl;

    return 0;
}
