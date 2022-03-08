# RISC-V ISA SIMULATOR
### ECE586 Final Project - Group 9 ;)
#### Yashodhan Wagle, Supreet Gulavani, Ramaa Potnis, Preksha Gandhi
----------------------------------------------------------------------
### How to run:
- Assuming you have GCC and Make installed, `cd` to the project directory and run
    
    `make debug` : Build with debug info printed to console

    `make release` : Build without debug info printed to the console
    
    `make clean`   : Build gets cleaned i.e rm -rf

- You should now have the executable named `ece586_isa_simulator` in the top directory.
- Run it as follows:

    ```$ ./ece586_isa_simulator <input_mem_file> <output_mem_file> <program_counter> <stack_address>```

- For example, my input mem file is `input.mem` and I want output in the file named `output.txt` setting the `program counter` `0` and `stack address` to `65535`, I will run:

    ```$ ./ece586_isa_simulator input.mem output.txt 0 65535 ```
