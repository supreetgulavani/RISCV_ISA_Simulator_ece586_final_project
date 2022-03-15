# RISC-V ISA SIMULATOR
### ECE586 Final Project - Group 9 ;)
#### Yashodhan Wagle, Supreet Gulavani, Ramaa Potnis, Preksha Gandhi
----------------------------------------------------------------------
### How to run:
- Assuming you have GCC and Make installed, `cd` to the project directory and run
    
    `make debug` : Build with debug info printed to console

    `make release` : Build without debug info printed to the console
    
    `make clean`   : Build gets cleaned i.e rm -rf
    
    `make step`   : Build with ability to step through instructions
    
    `make breakpoint`   : Build with ability to create multiple breakpoints (runtime)

- You should now have the executable named `ece586_isa_simulator` in the top directory.
- Run it as follows:

    ```$ ./ece586_isa_simulator <input_mem_file> <output_mem_file> <program_counter> <stack_address> <verbose_mode> <debug_mode>```

- For example, input mem file is `input.mem` and output in the file named `output.txt` setting the `program counter` `0` and `stack address` to `65535`. 
  Select `verbose mode` by adding  `1` or `0` . Select `debug mode` by adding  `1` or `0`
  
    ```$ ./ece586_isa_simulator input.mem output.txt 0 65535 1 0 ```
