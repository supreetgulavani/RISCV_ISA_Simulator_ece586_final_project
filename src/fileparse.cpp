#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "commondefs.h"
#include "fileparse.h"
#include "request.h"
#include "isasim.h"

/*
 * Parses the input trace string
 * Prints to debug console if built in debug mode
 */


void read_file(std::string ip_string, request& req)
{
    uint32_t substr_begin = 0, substr_end, pos = 0;

    std::string tokens[2];
    uint8_t token_count = 0;

    bool token_valid {false};

    /*std::string fn = "yes.mem";
    if(fn.substr(fn.find_last_of(".") + 1) != "mem") {
        std::cout << "Not a mem file. Please cross compile using rvgcc first." << std::endl;
    } 
    else {
        std::cout << "Parsing.." << std::endl;
    }*/

    // Traverse the line and get 3 tokens
    while (pos < ip_string.length()-1) {
        // Find the first non-whitespace character
        while (isspace(ip_string[pos])) {
            pos++;
        }
        substr_begin = pos;

        // Find the next whitespace character
        while (!(isspace(ip_string[pos])) && (pos < ip_string.length())) {
            pos++;
        }
        substr_end = pos;

        // The first token will have a colon adjacent to the number, check for that as well
        if (token_count == 0)
            substr_end--;
        
        // Data is between the two positions we found out
        if (substr_begin != substr_end) {
            if(substr_end < 1000){
            tokens[token_count] = ip_string.substr(substr_begin, substr_end - substr_begin);
            #ifdef DEBUG
            //std::cout << "Begin: " << substr_begin << " End: " << substr_end << std::endl;
            std::cout << tokens[token_count] << "\t";
            #endif

            token_count++;
            token_valid = true;
            }
            else
                break;
        }
        else {
            break;
        }

        // Invalid input checking
        if (token_count > 2) {
            std::cerr << "Invalid input! - " << ip_string << std::endl;
            exit(1);
        }
    }

    //Get the data into variables
    if (token_valid == true) {
        req.instruction_location = std::stoi(tokens[0], nullptr, 16); 
        req.instruction = std::stoull(tokens[1], nullptr, 16);
        req.load_mem(req);
    } else {
        req.valid = false;
    }

}