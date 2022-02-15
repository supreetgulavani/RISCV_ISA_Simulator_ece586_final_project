#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"


uint64_t stack_pointer = 65535;

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
    if (argc < 3) {
        std::cerr << "Wrong command..\n\n";
        std::cerr << "Usage: ./ece586_isa_simulator <input_mem_file> <output_mem_file>" << std::endl;
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
    
    // Instantiate DRAM Controller

    request req; 

    // Print starting message
    std::cout << "\n -- Starting Simulation -- \n" << std::endl;

    while (true) {
        // Check if we can read in a request
        if ((ip_mem_fstream->is_open())) {
            // Read a new line
            ip_string = "";
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
    
            op  << req.program_counter << "\t" << std::hex <<req.address << "\t" << std::dec << stack_pointer << std::endl;
            std::cout << op.str();
            mem_fstream << op.str();
            
        }
          if (!(ip_mem_fstream->is_open())) {
            std::cout << "\n -- Simulation Over! -- \n" << std::endl;
            break;
          }
    }
    // Free the filestream heap
    delete ip_mem_fstream;

    // Close output file
    mem_fstream.close();

    return 0;
}
