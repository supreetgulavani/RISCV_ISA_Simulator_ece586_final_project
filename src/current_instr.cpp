#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"


int32_t current_instr::get_signed_i_imm(uint32_t i_imm){
    return((i_imm & 0xFFF) | ((i_imm & 0x800) ? 0xFFFFF000 : 0));
}

int32_t current_instr::get_signed_s_imm(uint32_t s_imm){
    return((s_imm & 0xFFF) | ((s_imm & 0x800) ? 0xFFFFF000 : 0));
}

int32_t current_instr::get_signed_b_imm(uint32_t b_imm){
    return((b_imm & 0x1FFF) | ((b_imm & 0x1000) ? 0xFFFFE000 : 0));
}

int32_t current_instr::get_signed_j_imm(uint32_t j_imm){
    return((j_imm & 0x1FFFFF) | ((j_imm & 0x100000) ? 0xFFE00000 : 0));
}

void current_instr::print_instr(std::string str) {
    if (verbose){
        std::cout << str << std::endl;
    }
}


void current_instr::instr_execution(uint32_t r[]){
    
    switch (opcode){
    case r_type_opcode:
        switch(funct7) {
        case 0x00:
            switch(funct3) {
                //ADD: Addition
                case add_funct3: 
                                print_instr("ADD Instruction Detected");
                                r[rd] = (int)r[rs1] + (int)r[rs2];
                break;

                //XOR
                case xor_funct3: 
                                print_instr("XOR Instruction Detected");
                                r[rd] = r[rs1] ^ r[rs2];
                break;

                //OR
                case or_funct3: 
                                print_instr("OR Instruction Detected");
                                r[rd] = r[rs1] | r[rs2];
                break;

                //AND 
                case and_funct3: 
                                print_instr("AND Instruction Detected");
                                r[rd] = r[rs1] & r[rs2];
                break;
                
                //SLL : Shift Logical Left
                case sll_funct3: 
                                print_instr("SLL Instruction Detected");
                                r[rd] = r[rs1]  << r[rs2];           
                            
                break;

                //SRL : Shift Logical Right
                case srl_funct3: 
                                print_instr("SRL Instruction Detected");
                                r[rd] = r[rs1] >> r[rs2];          
                break;

                //SLT : Set Less Than
                case slt_funct3: 
                                print_instr("SLT Instruction Detected");
                                r[rd] =  (int)r[rs1] < (int)r[rs2] ? 1 : 0;
                break;

                //SLTU : Set Less Than Unsigned
                case sltu_funct3: 
                                print_instr("SLTU Instruction Detected");
                                r[rd] =  (unsigned)r[rs1] < (unsigned)r[rs2] ? 1 : 0;  
                break;
            }
        break;
		
        case 0x20:
            switch(funct3) {
                //SUB : Subtraction
                case sub_funct3: 
                                print_instr("SUB Instruction Detected");

                break;
                
                //SRA : Shift Right Arithmetic
                case sra_funct3: 
                                print_instr("SRA Instruction Detected");
                                r[rd] = ((int)r[rs1] ^ 0x0) >> (int)r[rs2];
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
                            r[rd] = r[rs1] + get_signed_i_imm(i_imm);
            break;

            //XORI (Immediate) 
            case xori_funct3: 
                            print_instr("XORI Instruction Detected");
                            r[rd] = r[rs1] ^ i_imm;
            break;

            //ORI (Immediate) 
            case ori_funct3: 
                            print_instr("ORI Instruction Detected");
                            r[rd] = r[rs1] | i_imm;
            break;

            //ANDI (Immediate) 
            case andi_funct3: 
                            print_instr("ANDI Instruction Detected");
                            r[rd] = r[rs1] & i_imm;
            break;

            //SLLI : Shift Logical Left Immediate
            case slli_funct3: 
                            print_instr("SLLI Instruction Detected");
                            r[rd] = r[rs1] << r[i_imm];      
            break;

            //write one for srai: they are different
            case srli_srai_funct3: 
                    switch(funct7){
                        case srai_funct7:
                                        print_instr("SRAI Instruction Detected");
                                        r[rd] = ((int)r[rs1] ^ 0x0) >> i_imm;  
                        break;
                        case srli_funct7:
                                        print_instr("SRLI Instruction Detected");
                                        r[rd] = r[rs1] >> i_imm;   
                        break;
                    }
                       
            break;

            //SLTI : Set Less Than Immediate
            case slti_funct3: 
                            print_instr("SLTI Instruction Detected");
                            r[rd] =  (int)r[rs1] < (int)i_imm ? 1 : 0;
            break;

            //SLTIU : Set Less Than Immediate Unsigned
            case sltiu_funct3: 
                            print_instr("SLTIU Instruction Detected");
                            r[rd] =  (unsigned)r[rs1] < (unsigned)i_imm ? 1 : 0;  
            break;
        }
    break;

    case 0x3:  // i type 0x3
        switch(funct3){
            //LB : Load Byte
            case lb_funct3: 
                            print_instr("LB Instruction Detected");
                             //Develop your LB instr implementation here
            break;

            //LH : Load Halfword
            case lh_funct3: 
                            print_instr("LH Instruction Detected");
                            //Develop your LH instr implementation here
            break;

            //LW : Load Word
            case lw_funct3: 
                           print_instr("LW Instruction Detected");
                           //Develop your LW instr implementation here
            break;

            //LBU : Load Byte Unsigned
            case lbu_funct3: 
                            print_instr("LBU Instruction Detected");
                            //Develop your LBU instr implementation here
            break;

            //LHU : Load Half Unsigned
            case lhu_funct3: 
                            print_instr("LHU Instruction Detected");
                            //Develop your LHU instr implementation here
            break;
        }
    break;

    case 0x67:  // i type 0x67
        switch(funct3){
            //JALR : Jump & Link Register
            case jalr_funct3: 
                            print_instr("JALR Instruction Detected");
                            //Develop your LB instr implementation here
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
            //BEQ : Branch if Equal
            case beq_funct3: 
                          print_instr("BEQ Instruction Detected");
                            if(r[rs1] == r[rs2])
                                c_pc = c_pc + b_imm ;
            break;

            //BNE : Branch if Not Equal
            case bne_funct3: 
                            print_instr("BNE Instruction Detected");
                           if(r[rs1] != r[rs2])
                                 c_pc = c_pc + b_imm ;

            break;

            //BLT : Branch if Less Than
            case blt_funct3: 
                            print_instr("BLT Instruction Detected");
                            if(r[rs1] < r[rs2])
                                c_pc = c_pc + b_imm ;
            break;

            //BGE : Branch if Greater than or Equal 
            case bge_funct3: 
                           print_instr("BGE Instruction Detected");
                            if(r[rs1] > r[rs2])
                                c_pc = c_pc + b_imm ;
            break;
        
            //BLTU : Branch if Less Than Unsigned
            case bltu_funct3: 
                            print_instr("BLTU Instruction Detected");
                        if((unsigned)r[rs1] >= (unsigned)r[rs2])
                            c_pc = c_pc + b_imm ;
            break;
        
            //BGE : Branch if Greater than or Equal Unsigned
            case bgeu_funct3: 
                            print_instr("BGEU Instruction Detected");
                            if(r[rs1] >= r[rs2])
                                c_pc = c_pc + b_imm ;
            break;
        }
    break;

    //LUI: Load Upper Immediate 
    case 0x37: 
                print_instr("LUI Instruction Detected");
                r[rd] = u_imm;
    break;

    //AUIPC: Add Upper Immediate to PC
    case 0x17: 
                print_instr("AUIPC Instruction Detected");
                r[rd] = c_pc + u_imm;           //20 and lower 12 zero: check this instr again
    break;

    //JAL : Jump and Link
    case j_type_opcode: 
                       print_instr("JAL Instruction Detected");
                       //Develop your JAL instr implementation here
    break;

    case s_type_opcode: 
        switch(funct3){
        case sw_funct3: 
                        print_instr("SW Instruction Detected");
                        //r[rd] = ;
        }
    }

    if (verbose){
        std::cout << "Result:\t" << std::hex << r[rd] << "\n" << std::endl;
        std::cout << "Register values are:" << std::endl;
        int reg_elements = 0;
        for (int i = reg_elements; i <= 31; i++){
            std::cout << i << ":" << std::uppercase << std::hex << r[i] << "\t";
        }
        std::cout << "\nProgram Counter:" << std:: uppercase << std::hex << c_pc << "\n" << std::endl;
    }    

}

