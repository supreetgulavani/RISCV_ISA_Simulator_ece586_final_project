# RISC-V ISA SIMULATOR
### ECE586 Final Project - Group 9 ;)
#### Yashodhan Wagle, Supreet Gulavani, Ramaa Potnis, Preksha Gandhi
----------------------------------------------------------------------

### How to run:
- Assuming you have GCC and Make installed, `cd` to the project directory and run
    
    `make debug` : Build with debug info printed to console

    `make release` : Build without debug info printed to the console

- You should now have the executable named `ece585_memory_controller` in the top directory.
- Run it as follows:

    ```$ ./ece585_memory_controller <input_trace_file> <output_dram_commands_file>```

- For example, if my input memory request trace is `ip_trace.txt` and I want output in the file named `output.txt`, I will run:

    ```$ ./ece585_memory_controller ip_trace.txt output.txt```

### Configuration Options
- Bank parallelism:
    - To enable, make sure the line `#define BANK_PARALLELISM` in `include/commondefs.h` is _uncommented_.
    - To disable, make sure the line is commented.
    - Note: You need to `make clean` and recompile the project for the effect to take place.
