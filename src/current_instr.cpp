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

uint64_t current_instr::get_power (uint64_t base, uint64_t exponent) {
     uint64_t res_power = 1;
     for (uint64_t i = 0; i < exponent; i++) {
         res_power *= base;      
     }
     return(res_power);
 }

void current_instr::instr_execution(uint32_t r[]){

    bool pc_changed = false;

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
                                r[rd] = r[rs1] << (r[rs2] % 32);       
                break;

                //SRL : Shift Logical Right
                case srl_funct3: 
                                print_instr("SRL Instruction Detected");
                                r[rd] = r[rs1] >> r[rs2];          
                break;

                //SLT : Set Less Than
                case slt_funct3: 
                                print_instr("SLT Instruction Detected");
                                r[rd] =  (int)r[rs1] < (int)r[rs2] ? 0x00000001 : 0x0;
                break;

                //SLTU : Set Less Than Unsigned
                case sltu_funct3: 
                                print_instr("SLTU Instruction Detected");
                                r[rd] =  r[rs1] < r[rs2] ? 0x00000001 : 0x0;  
                break;
            }
        break;
		
        case 0x20:
            switch(funct3) {
                //SUB : Subtraction
                case sub_funct3: 
                                print_instr("SUB Instruction Detected");
                                r[rd] = (int)r[rs1] - (int)r[rs2];
                break;
                
                //SRA : Shift Right Arithmetic
                case sra_funct3: 
                                print_instr("SRA Instruction Detected");
                                if (r[rs1] & 80000000)
                                    r[rd] = (r[rs1] >> r[rs2]) | ((2**(r[rs2]+1) - 1) << (32-r[rs2]));
                                else
                                    r[rd] = r[rs1] >> r[rs2];
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
                            r[rd] = r[rs1] << ((int)i_imm % 32);      
            break;

            //SRAI, SRLI : Shift Right Arithmetic Immediate, Shift Right Logical Immediate
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
                        //loading offset i.e immediate value added with are base address into destination
                        print_instr("LB Instruction Detected");
						//r[rd] = ((r[rs1] + i_imm) & 0x8000) ? ((r[rs1] + i_imm) | 0xFFFF0000) : ((r[rs1] + i_imm) & 0x0000FFFF); 
						 
            break;

            //LH : Load Halfword
            case lh_funct3: 
						 /*std::cout << "LH instruction Detected" << std::endl; //need  to define lh, Lower8, Upper8
						 if ((i_imm + r[rs1]) & 0x00000001))
						 {
							cout<<"The addresses are not alligned";
						 }
						 else
						 {
						 Lower8 = memory_array[i_imm + r[rs1]];
						 Upper8 = memory_array[i_imm + r[rs1] + 1];
						 lh = (Upper8<<8)||(Lower8);
						 r[rd] = (lh & 0x8000) ? (lh | 0xFFFF0000) : (lh & 0x0000FFFF);
						 }
				
						 std::cout << "Load HalfWord Result:" << std:: hex << r[rd] << "\n" << std::endl;*/
            break;

            //LW : Load Word 
            case lw_funct3:
						 /*std::cout << "LW instruction Detected" << std::endl;
						 if ((i_imm + r[rs1]) & 0x00000002)
						 {
							cout<<"The addresses are not alligned";
						 }
						 else
						 {
						 Lower8_0 = memory_array[i_imm + r[rs1]];
						 Lower16_8 = memory_array[i_imm + r[rs1] + 1];
						 Lower24_16 = memory_array[i_imm + r[rs1] + 2];
						 Upper32_24 = memory_array[i_imm + r[rs1] + 3]; 
						 r[rd] = (Upper32_24<<24)|(Lower24_16<<16)|(Lower16_8<<8)|(Lower8_0) ;
						 }
						 std::cout << "Load Word Result:" << std:: hex << r[rd] << "\n" << std::endl;*/
            break;

            //LBU : Load Byte Unsigned
            case lbu_funct3: 
						 /* std::cout << "LBU instruction Detected" << std::endl;
						  r[rd] = (memory_array[r[rs1] + i_imm])|(0x00000000);
                          std::cout << "Load Byte Unisgned Result:" << std:: hex << r[rd] << "\n" << std::endl;*/
            break;

            //LHU : Load Half Unsigned
            case lhu_funct3: 
						  /*std::cout << "LHU instruction Detected" << std::endl;
						  if ((i_imm + r[rs1]) & 0x00000001)
						 {
							cout<<"The addresses are not alligned";
						 } //check alignment
						 else
						 {
						  Lower8 = memory_array[i_imm + r[rs1]];
						  Upper8 = memory_array[i_imm + r[rs1] + 1];
						  lh = (Upper8<<8)||(Lower8);
						  r[rd] = lh & 0x0000FFFF;
						 }
						  std::cout << "LHU Result:" << std:: hex << r[rd] << "\n" << std::endl;*/
        
            break;
        }
    break;


    case 0x67:  // i type 0x67
        switch(funct3){
            //JALR : Jump & Link Register
            case jalr_funct3: 
                            print_instr("JALR Instruction Detected");
                            //c_pc = r[rs1] + i_imm;
                            //pc_changed = true;
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
                            if (r[rs1] == r[rs2]){
                                c_pc += b_imm;
                                pc_changed = true;
                            }
            break;

            //BNE : Branch if Not Equal
            case bne_funct3: 
                            print_instr("BNE Instruction Detected");    
                            std:: cout << (unsigned)b_imm << std::endl;
                           if (r[rs1] != r[rs2]) {
                                c_pc += b_imm;
                                pc_changed = true;
                            }    
            break;

            //BLT : Branch if Less Than
            case blt_funct3: 
                            print_instr("BLT Instruction Detected");
                            if (r[rs1] < r[rs2]) {
                                c_pc += b_imm;
                                pc_changed = true;
                            }
            break;

            //BGE : Branch if Greater than or Equal 
            case bge_funct3: 
                           print_instr("BGE Instruction Detected");
                            if(r[rs1] > r[rs2]) {
                                c_pc += b_imm ;
                                pc_changed = true;
                            }
            break;
        
            //BLTU : Branch if Less Than Unsigned
            case bltu_funct3: 
                            print_instr("BLTU Instruction Detected");
                            if ((unsigned)r[rs1] >= (unsigned)r[rs2]) {
                                c_pc += b_imm ;
                                pc_changed = true;
                            }

            break;
        
            //BGE : Branch if Greater than or Equal Unsigned
            case bgeu_funct3: 
                            print_instr("BGEU Instruction Detected");
                            if (r[rs1] >= r[rs2]) {
                                c_pc += b_imm;
                                pc_changed = true;
                            }
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
                        c_pc += get_signed_j_imm(j_imm); 
                        pc_changed = true;
                        //r[rd] = c_pc + 4;                     
    break;

    case s_type_opcode: 
        switch(funct3){
        case sw_funct3: 
                        print_instr("SW Instruction Detected");
                        //((memory_array[r[rs1] + s_imm + 3]) << 24) | ((memory_array[r[rs1] + s_imm + 2]) << 16) | ((memory_array[r[rs1] + s_imm + 1]) << 8) | (memory_array[r[rs1] + s_imm]) = r[rs2] ;
        break;

        case sb_funct3: 
                        print_instr("SB Instruction Detected");
                        //((memory_array[r[rs1] + s_imm + 1]) << 8) | (memory_array[r[rs1] + s_imm]) = r[rs2] ;
        break;

        case sh_funct3: 
                        print_instr("SH Instruction Detected");
                        //memory_array[r[rs1] + s_imm] = r[rs2]; 
        break;
        }
    break;
    }

    if (!pc_changed)
        c_pc =  c_pc + 4;

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

