#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"


int32_t current_instr::get_signed_i_imm(uint32_t i_imm){
    return((i_imm & 0xFFF) | ((i_imm & 0x800) ? 0xFFFFF000 : 0x00000000));
}

int32_t current_instr::get_signed_s_imm(uint32_t s_imm){
    return((s_imm & 0xFFF) | ((s_imm & 0x800) ? 0xFFFFF000 : 0x00000000));
}

int32_t current_instr::get_signed_b_imm(uint32_t b_imm){
    return((b_imm & 0x1FFF) | ((b_imm & 0x1000) ? 0xFFFFE000 : 0));
}

int32_t current_instr::get_signed_j_imm(uint32_t j_imm){
    return((j_imm & 0x1FFFFF) | ((j_imm & 0x100000) ? 0xFFE00000 : 0));
}

void current_instr::print_instr(std::string str) {
    std:: stringstream op;
    if (verbose){
        op << str << std::endl;
        std::cout << op.str();
        current_instr_reg_file << op.str();
    }
}

// Its over 9 thousanddddd
uint64_t current_instr::get_power (uint64_t base, uint64_t exponent) {
     uint64_t res_power = 1;
     for (uint64_t i = 0; i < exponent; i++) {
         res_power *= base;      
     }
     return(res_power);
 }

void current_instr::instr_execution(uint32_t r[]){

    r[2] = c_sp;
    bool pc_changed = false;
    
    // Used to print upper portion of the memory for stack 
    //int mem_elements = 65300;

    switch (opcode){
    case r_type_opcode:
        switch(funct7) {
        case 0x00:
            switch(funct3) {
                //ADD: Addition
                case add_funct3: 
                    print_instr("ADD Instruction Detected");
                    r[rd] = (int)r[rs1] + (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //XOR
                case xor_funct3: 
                    print_instr("XOR Instruction Detected");
                    r[rd] = r[rs1] ^ r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //OR
                case or_funct3: 
                    print_instr("OR Instruction Detected");
                    r[rd] = r[rs1] | r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //AND 
                case and_funct3: 
                    print_instr("AND Instruction Detected");
                    r[rd] = r[rs1] & r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;
                
                //SLL : Shift Logical Left
                case sll_funct3: 
                    print_instr("SLL Instruction Detected");
                    r[rd] = r[rs1] << (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //SRL : Shift Logical Right
                case srl_funct3: 
                    print_instr("SRL Instruction Detected");
                    r[rd] = r[rs1] >> (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;        
                break;

                //SLT : Set Less Than
                case slt_funct3: 
                    print_instr("SLT Instruction Detected");
                    r[rd] =  (int)r[rs1] < (int)r[rs2] ? 0x00000001 : 0x0;
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //SLTU : Set Less Than Unsigned
                case sltu_funct3: 
                    print_instr("SLTU Instruction Detected");
                    r[rd] =  r[rs1] < r[rs2] ? 0x00000001 : 0x0;
                    if (rd == 0)
                        r[rd] = 0x0;
                break;
            }
        break;
		
        case 0x20:
            switch(funct3) {
                //SUB : Subtraction
                case sub_funct3: 
                    print_instr("SUB Instruction Detected");
                    r[rd] = (int)r[rs1] - (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;
                
                //SRA : Shift Right Arithmetic
                case sra_funct3: 
                    print_instr("SRA Instruction Detected");
                    if (r[rs1] & 80000000){
                        r[rd] = (r[rs1] >> (int)r[rs2]) | ((get_power(2, ((int)r[rs2]+1)) - 1) << (32-(int)r[rs2]));
                        if (rd == 0)
                            r[rd] = 0x0;
                    }
                    else{
                        r[rd] = r[rs1] >> (int)r[rs2];
                        if (rd == 0)
                            r[rd] = 0x0;
                    }
                break;
            }   
        break;

        case 0x01:
            switch(funct3) {
                //MUL : Multiplication
                case mul_funct3: 
                    print_instr("MUL Instruction Detected");
                    r[rd] = (int)r[rs1] * (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //MULH : Multiplication
                case mulh_funct3: 
                    print_instr("MULH Instruction Detected");
                    r[rd] = ((int64_t)r[rs1] * (int64_t)r[rs2]) >> 32;
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //MULHSU : Multiplication
                case mulhsu_funct3: 
                    print_instr("MULHSU Instruction Detected");
                    r[rd] = ((int64_t)r[rs1] * (uint64_t)r[rs2]) >> 32;
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //MULHU : Multiplication
                case mulhu_funct3: 
                    print_instr("MULHU Instruction Detected");
                    r[rd] = ((uint64_t)r[rs1] * (uint64_t)r[rs2]) >> 32;
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //DIV : Multiplication
                case div_funct3: 
                    print_instr("DIV Instruction Detected");
                    if (r[rs2] == 0x0){
                        print_instr("Exception: divide by 0");
                        exit(1);
                    }
                    r[rd] = (int)r[rs1] / (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //DIVU : Multiplication
                case divu_funct3: 
                    print_instr("DIVU Instruction Detected");
                    if (r[rs2] == 0x0){
                        print_instr("Exception: divide by 0");
                        exit(1);
                    }
                    r[rd] = r[rs1] / r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //REM : Multiplication
                case rem_funct3: 
                    print_instr("REM Instruction Detected");
                    if (r[rs2] == 0x0){
                        print_instr("Exception: divide by 0");
                        exit(1);
                    }
                    r[rd] = (int)r[rs1] % (int)r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;

                //REMU : Multiplication
                case remu_funct3: 
                    print_instr("REMU Instruction Detected");
                    if (r[rs2] == 0x0){
                        print_instr("Exception: divide by 0");
                        exit(1);
                    }
                    r[rd] = r[rs1] % r[rs2];
                    if (rd == 0)
                        r[rd] = 0x0;
                break;
            }
        break;

        }
    break;

    case 0x13:  // i type 0x13
        switch(funct3){
            //ADDI : Addition Immediate
            case addi_funct3: 
                print_instr("ADDI Instruction Detected");
                //std::cout << "r[rs1]: " << r[rs1] << std::endl;
                //std::cout << "i_imm: " << get_signed_i_imm(i_imm) << std::endl;
                r[rd] = (int)r[rs1] + get_signed_i_imm(i_imm);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //XORI (Immediate) 
            case xori_funct3: 
                print_instr("XORI Instruction Detected");
                r[rd] = r[rs1] ^ get_signed_i_imm(i_imm);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //ORI (Immediate) 
            case ori_funct3: 
                print_instr("ORI Instruction Detected");
                r[rd] = r[rs1] | get_signed_i_imm(i_imm);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //ANDI (Immediate) 
            case andi_funct3: 
                print_instr("ANDI Instruction Detected");
                r[rd] = r[rs1] & get_signed_i_imm(i_imm);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //SLLI : Shift Logical Left Immediate
            case slli_funct3: 
                print_instr("SLLI Instruction Detected");
                r[rd] = r[rs1] << get_signed_i_imm(i_imm);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //SRAI, SRLI : Shift Right Arithmetic Immediate, Shift Right Logical Immediate
            case srli_srai_funct3: 
                    switch(funct7){
                        case srai_funct7:
                            print_instr("SRAI Instruction Detected");
                            if (r[rs1] & 80000000)
                                r[rd] = (r[rs1] >> get_signed_i_imm(i_imm)) | ((get_power(2, (get_signed_i_imm(i_imm)+1)) - 1) << (32-get_signed_i_imm(i_imm)));
                            else
                                r[rd] = r[rs1] >> get_signed_i_imm(i_imm);
                            if (rd == 0)
                                r[rd] = 0x0;
                        break;
                        
                        case srli_funct7:
                            print_instr("SRLI Instruction Detected");
                            r[rd] = r[rs1] >> get_signed_i_imm(i_imm);
                            if (rd == 0)
                                r[rd] = 0x0;
                        break;
                    }
                       
            break;

            //SLTI : Set Less Than Immediate
            case slti_funct3: 
                print_instr("SLTI Instruction Detected");
                r[rd] =  (int)r[rs1] < get_signed_i_imm(i_imm) ? 1 : 0;
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //SLTIU : Set Less Than Immediate Unsigned
            case sltiu_funct3: 
                print_instr("SLTIU Instruction Detected");
                r[rd] =  r[rs1] < i_imm ? 1 : 0;
                if (rd == 0)
                    r[rd] = 0x0;
            break;
        }
    break;

    case 0x3:  // i type 0x3
        switch(funct3){
            //LB : Load Byte
            case lb_funct3:
                print_instr("LB Instruction Detected");
                if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFF){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
				r[rd] = (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)] & 0x000000FF) | ((memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)] & 0x00000080) ? 0xFFFFFF00 : 0x0);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //LH : Load Halfword
            case lh_funct3: 
                print_instr("LH Instruction Detected");
                if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFE){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
                else if (((int)r[rs1] + get_signed_i_imm(i_imm)) & 0x00000001)
                    print_instr("Warning: address unaligned");
                r[rd] = (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)]) | (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 1] << 8) | ((memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 1] & 0x00000080) ? 0xFFFF0000 : 0x0);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //LW : Load Word 
            case lw_funct3:
			    print_instr("LW Instruction Detected");
                if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFC){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
                else if (((int)r[rs1] + get_signed_i_imm(i_imm)) & 0x00000003)
                    print_instr("Warning: address unaligned");
                r[rd] = (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)]) | (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 1] << 8) | (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 2] << 16) | (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 3] << 24);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //LBU : Load Byte Unsigned
            case lbu_funct3: 
				print_instr("LBU Instruction Detected");
                if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFF){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
				r[rd] = (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)]) | (0x00000000);
                if (rd == 0)
                    r[rd] = 0x0;
            break;

            //LHU : Load Half Unsigned
            case lhu_funct3: 
				print_instr("LHU Instruction Detected");
                if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFE){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
                else if (((int)r[rs1] + get_signed_i_imm(i_imm)) & 0x00000001)
                    print_instr("Warning: address unaligned");
                r[rd] = (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm)] & 0x000000FF) | (memory_array[(int)r[rs1] + get_signed_i_imm(i_imm) + 1] << 8);
                if (rd == 0)
                    r[rd] = 0x0;
            break;
        }
    break;


    case 0x67:  // i type 0x67
        switch(funct3){
            //JALR : Jump & Link Register
            case jalr_funct3: 
                print_instr("JALR Instruction Detected");
                r[rd] = c_pc + 4;
                if (rd == 0)
                    r[rd] = 0x0;
                c_pc = ((int)r[rs1] + get_signed_i_imm(i_imm)) << 1;
                if (c_pc & 0x00000003){
                    print_instr("Exception: Unaligned jump");
                    exit(1);
                }
                else if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFC){
                    print_instr("Exception: address out of bound");
                    exit(1);
                }
                pc_changed = true;
            break;
            }
    break;

    case 0x73:  // i type 0x73
        switch(funct3){
            //ECALL and EBREAK : 
            case ecall_ebreak_funct3: 
                switch(i_imm){
                case 0x0: 
                    print_instr("ECALL Instruction Detected");
                    //Develop your ECALL instr implementation here
                    switch (r[0x11]){
                    case 0x5E:  // EXIT
                        r[0xA] = 0x0;
                        exit(1);
                    break;
                    
                    case 0x3F:  // READ
                        if (r[0xA] == 0x0){
                            char filename[r[0x0C]];
                            std::cin.getline(filename, (r[0x0C]+1));
                            r[0xA] = std::cin.gcount() - 1;
                            int i = 0;
                            for (i = 0; i < r[0x0C]; i++){
                                memory_array[r[0x0B] + i] = (const char)*(filename + i);
                                //std::cout << memory_array[r[0x0B] + i] << std::endl;
                            }
                        }
                        else{
                            print_instr("Exception: Invalid FILE DESCRIPTOR");
                            exit(1);
                        }
                    break;

                    case 0x40:  // WRITE
                        if (r[0xA] == 0x1){
                            int i = 0;
                            for (i = 0; i < r[0x0C]; i++){
                                std::cout << memory_array[r[0x0B] + i];
                                if (i > 65535 - r[0x0B])
                                    break;
                            }
                            r[0xA] = i;
                            std::cout << std::endl;
                        }
                        else{
                            print_instr("Exception: Invalid FILE DESCRIPTOR");
                            exit(1);
                        }
                    break;

                    default: print_instr("Exception: Invalid or Unsupported ECALL");
                            exit(1);
                    break;
                    }
                break;

                case 0x1: 
                    print_instr("EBREAK Instruction Detected");
                    //Develop your EBREAK instr implementation here
                break;
            }
            break;    
        }
   
    break;

    case b_type_opcode:
        switch(funct3){
            // BEQ : Branch if Equal
            case beq_funct3: 
                print_instr("BEQ Instruction Detected");
                if (r[rs1] == r[rs2]){
                    c_pc += get_signed_b_imm(b_imm);
                    if (c_pc & 0x00000003){
                        print_instr("Exception: Unaligned jump");
                        exit(1);
                    }
                    pc_changed = true;
                }
            break;

            // BNE : Branch if Not Equal
            case bne_funct3:
                print_instr("BNE Instruction Detected");
                if (r[rs1] != r[rs2]){
                c_pc += get_signed_b_imm(b_imm);
                if (c_pc & 0x00000003){
                    print_instr("Exception: Unaligned jump");
                    exit(1);
                }
                pc_changed = true;
                }
            break;

            // BLT : Branch if Less Than
            case blt_funct3:
                print_instr("BLT Instruction Detected");
                if ((int)r[rs1] < (int)r[rs2]){
                    c_pc += get_signed_b_imm(b_imm);
                    if (c_pc & 0x00000003){
                        print_instr("Exception: Unaligned jump");
                        exit(1);
                    }
                    pc_changed = true;
                }
            break;

            // BGE : Branch if Greater than or Equal 
            case bge_funct3: 
                print_instr("BGE Instruction Detected");
                if((int)r[rs1] >= (int)r[rs2]) {
                    c_pc += get_signed_b_imm(b_imm);
                    if (c_pc & 0x00000003){
                        print_instr("Exception: Unaligned jump");
                        exit(1);
                    }  
                    pc_changed = true;
                }
            break;
        
            // BLTU : Branch if Less Than Unsigned
            case bltu_funct3: 
                print_instr("BLTU Instruction Detected");
                if ((int)r[rs1] < (int)r[rs2]) {
                c_pc += get_signed_b_imm(b_imm);
                if (c_pc & 0x00000003){
                    print_instr("Exception: Unaligned jump");
                    exit(1);
                    }
                pc_changed = true;
                }
            break;
        
            // BGEU : Branch if Greater than or Equal Unsigned
            case bgeu_funct3: 
                print_instr("BGEU Instruction Detected");
                if ((int)r[rs1] >= (int)r[rs2]) {
                c_pc += get_signed_b_imm(b_imm);
                if (c_pc & 0x00000003){
                    print_instr("Exception: Unaligned jump");
                    exit(1);
                }
                pc_changed = true;
                }
            break;
        }
    break;

    //LUI: Load Upper Immediate 
    case 0x37: 
        print_instr("LUI Instruction Detected");
        r[rd] = u_imm;
        if (rd == 0)
            r[rd] = 0x0;
    break;

    //AUIPC: Add Upper Immediate to PC
    case 0x17: 
        print_instr("AUIPC Instruction Detected");
        r[rd] = (int)c_pc + (int)u_imm;
        if (rd == 0)
            r[rd] = 0x0;
    break;

    //JAL : Jump and Link
    case j_type_opcode: 
        print_instr("JAL Instruction Detected");
        r[rd] = c_pc + 4;
        if (rd == 0)
            r[rd] = 0x0;
        c_pc += get_signed_j_imm(j_imm); 
        if (c_pc & 0x00000003){
            print_instr("Exception: Unaligned jump");
            exit(1);
        }
        pc_changed = true;                    
    break;

    case s_type_opcode: 
        switch(funct3){
        case sw_funct3: 
            print_instr("SW Instruction Detected");
            std::cout << "r[rs2] (stuff to be saved): " << r[rs2] << std::endl;
            std::cout << "r[rs1] (addr where its to be saved): " << (int)r[rs1] + get_signed_s_imm(s_imm) << std::endl;
            if ((int)r[rs1] + get_signed_s_imm(s_imm) > 0xFFFC){
                print_instr("Exception: address out of bound");
                exit(1);
            }
            else if (((int)r[rs1] + get_signed_s_imm(s_imm)) & 0x00000003)
                print_instr("Warning: address unaligned");
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm) + 3] = (r[rs2] & 0xFF000000) >> 24; 
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm) + 2] = (r[rs2] & 0x00FF0000) >> 16;
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm) + 1] = (r[rs2] & 0x0000FF00) >> 8;
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm)]     = r[rs2] & 0x000000FF;

            //for (int i = mem_elements; i <= 65535; i++){
            //    std::cout << i << ":" << std::uppercase << std::hex << (int)memory_array[i] << "\t";
            //}
        break;

        case sb_funct3: 
            print_instr("SB Instruction Detected");
            if ((int)r[rs1] + get_signed_i_imm(i_imm) > 0x0000FFFF){
                print_instr("Exception: address out of bound");
                exit(1);
            }
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm)]     = r[rs2] & 0x000000FF;
        break;

        case sh_funct3: 
            print_instr("SH Instruction Detected");
            if ((int)r[rs1] + get_signed_s_imm(s_imm) > 0x0000FFFE){
                print_instr("Exception: address out of bound");
                exit(1);
            }
            else if (((int)r[rs1] + get_signed_s_imm(s_imm)) & 0x00000001)
                print_instr("Warning: address unaligned");
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm) + 1] = r[rs2] & 0x0000FF00;
            memory_array[(int)r[rs1] + get_signed_s_imm(s_imm)]     = r[rs2] & 0x000000FF; 
        break;
        }
    break;

    default: print_instr("Exception: Invalid Opcode");
            exit(1);
    break;
    }

    if (!pc_changed)
        c_pc =  c_pc + 4;
    
    c_sp = r[2];

    if (verbose){
        std:: stringstream op;
        //op << "Result:\t" << std::hex << r[rd] << "\n" << std::endl;
        op << "Register values are:" << std::endl;
        int reg_elements = 0;
        for (int i = reg_elements; i <= 31; i++){
            op << i << ":" << std::uppercase << std::hex << r[i] << "\t";
        }
        op << "\nProgram Counter:" << std:: uppercase << std::hex << c_pc << "\n" << std::endl;
        std::cout << op.str();
        current_instr_reg_file << op.str();
    }    

}
