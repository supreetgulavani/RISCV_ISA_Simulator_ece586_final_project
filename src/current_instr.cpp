#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "current_instr.h"

/*
isa_sim isa;
uint32_t current_instr::get_rd_value(uint8_t rd){
    if (rd == 0x0)
        uint32_t rd_value = isa.r0;
    else
        uint32_t rd_value = isa.r [rd]; 
};

uint32_t current_instr::get_rs1_value(uint8_t rs1){
};

uint32_t current_instr::get_rs2_value(uint8_t rs2){
};
*/


void current_instr::instr_execution(uint32_t r[]){

    //std::cout << "opcode: " << (int)opcode << std::endl; 
    
    switch (opcode){
    case r_type_opcode:
        switch(funct7) {
        case 0x00:
            switch(funct3) {
                //ADD: Addition
                case add_funct3: 
                                std::cout << "ADD instruction Detected" << std::endl;
                                r[rd] = (int)r[rs1] + (int)r[rs2];
                                std::cout << "ADD Result:" << std::hex << r[rd] << "\n" << std::endl;
                break;

                //XOR
                case xor_funct3: std::cout << "XOR instruction Detected" << std::endl;
                                r[rd] = r[rs1] ^ r[rs2];
                                std::cout << "XOR Result:" << std::hex << r[rd] << "\n" <<  std::endl;
                break;

                //OR
                case or_funct3: 
                                std::cout << "OR instruction Detected" << std::endl;
                                r[rd] = r[rs1] | r[rs2];
                                std::cout << "OR Result:" << std::hex << r[rd] << "\n" << std::endl;
                break;

                //AND 
                case and_funct3: std::cout << "AND instruction Detected" << std::endl;
                                r[rd] = r[rs1] & r[rs2];
                                std::cout << "AND Result:" << std::hex << r[rd] << "\n" << std::endl;
                break;
                
                //SLL : Shift Logical Left
                case sll_funct3: 
                                std::cout << "SLL instruction Detected" << std::endl;
                                r[rd] = r[rs1]  << r[rs2];      
                                std::cout << "Shift Logical Left Result:" << std:: hex << r[rd] << "\n" << std::endl;          
                            
                break;

                //SRL : Shift Logical Right
                case srl_funct3: 
                                std::cout << "SRL instruction Detected" << std::endl;
                                r[rd] = r[rs1] >> r[rs2];      
                                std::cout << "Shift Logical Right Result: " << std:: hex << r[rd] << "\n" << std::endl;     
                break;

                //SLT : Set Less Than
                case slt_funct3: 
                                std::cout << "SLT instruction Detected" << std::endl;
                                r[rd] =  (int)r[rs1] < (int)r[rs2] ? 1 : 0;
                                std::cout << "SLT Result:\t" << std::hex << r[rd] << "\n" << std::endl;
                break;

                //SLTU : Set Less Than Unsigned
                case sltu_funct3: 
                                std::cout << "SLTU instruction Detected" << std::endl;
                                r[rd] =  (unsigned)r[rs1] < (unsigned)r[rs2] ? 1 : 0;
                                std::cout << "SLTU Result:\t" << std::hex << r[rd] << "\n" << std::endl;    
                break;
            }
        break;

        case 0x20:
            switch(funct3) {
                //SUB : Subtraction
                case sub_funct3: 
                                std::cout << "SUB instruction Detected" << std::endl;

                break;
                
                //SRA : Shift Right Arithmetic
                case sra_funct3: 
                                std::cout << "SRA instruction Detected" << std::endl;
                                //r[rd] = r[rs1] >> r[rs2];   
                                r[rd] = r[rs1] < 0 ? ~(~r[rs1] >> r[rs2]) : r[rs1] >> r[rs2];
                                std::cout << "Shift Arithmetic Right  Result:" << std:: hex << r[rd] << "\n" << std::endl;
                break;
            }
        break;
        }
    break;

    case 0x13:  // i type 0x13
        switch(funct3){
            //ADDI : Addition Immediate
            case addi_funct3: 
                            std::cout << "\nADDI instruction Detected" << std::endl;
                            r[rd] = r[rs1] + ((i_imm & 0xFFF) | ((i_imm & 0x800) ? 0xFFFFF000 : 0));
                            std::cout << "ADDI Result:\t" << std:: hex << (int32_t)r[rd] << std::endl;
            break;

            //XORI (Immediate) 
            case xori_funct3: 
                            std::cout << "XOR1 instruction Detected" << std::endl;
                            r[rd] = r[rs1] ^ i_imm;
                            std::cout << "XORI Result:" << std::hex << r[rd] <<  (unsigned)i_imm << "\n" << std::endl;
            break;

            //ORI (Immediate) 
            case ori_funct3: 
                            std::cout << "ORI instruction Detected" << std::endl;
                            r[rd] = r[rs1] | i_imm;
                            std::cout << "ORI Result:" << std::hex << r[rd] <<  (unsigned)i_imm << "\n" << std::endl;
            break;

            //ANDI (Immediate) 
            case andi_funct3: 
                            std::cout << "ANDI instruction Detected" << std::endl;
                            r[rd] = r[rs1] & i_imm;
                            std::cout << "ANDI Result:" << std::hex << r[rd] << "\n" << std::endl;
            break;

            //SLLI : Shift Logical Left Immediate
            case slli_funct3: 
                            std::cout << "SLLI instruction Detected" << std::endl;
                            r[rd] = r[rs1] << r[i_imm];      
                            std::cout << "Shift Logical Left Immediate  Result:" << std:: hex << r[rd] << "\n" << std::endl;  
            break;

            //write one for srai
            case srli_srai_funct3: 
                            std::cout << "SRLI/SRAI instruction Detected" << std::endl;
                            r[rd] = r[rs1] >> r[i_imm];      
                            std::cout << "Shift Logical Right Immediate  Result:" << std:: hex << r[rd] << "\n" << std::endl;
            break;

            //SLTI : Set Less Than Immediate
            case slti_funct3: 
                            std::cout << "SLTI instruction Detected" << std::endl;
                            r[rd] =  (int)r[rs1] < (int)i_imm ? 1 : 0;
                            std::cout << "SLTI Result:\t" << std::hex << r[rd] << "\n" << std::endl;
            break;

            //SLTIU : Set Less Than Immediate Unsigned
            case sltiu_funct3: 
                            std::cout << "SLTIU instruction Detected" << std::endl;
                            std::cout << "SLTIU instruction Detected" << std::endl;
                            r[rd] =  (unsigned)r[rs1] < (unsigned)i_imm ? 1 : 0;
                            std::cout << "SLTIU Result:\t" << std::hex << r[rd] << "\n" << std::endl;  
            break;
        }
    break;

    case 0x3:  // i type 0x3
        switch(funct3){
            //LB : Load Byte
            case lb_funct3: std::cout << "LB instruction Detected" << std::endl;
            //Develop your LB instr implementation here
            break;

            //LH : Load Halfword
            case lh_funct3: std::cout << "LH instruction Detected" << std::endl;
        //Develop your LH instr implementation here
            break;

            //LW : Load Word
            case lw_funct3: std::cout << "LW instruction Detected" << std::endl;
        //Develop your LW instr implementation here
            break;

            //LBU : Load Byte Unsigned
            case lbu_funct3: std::cout << "LBU instruction Detected" << std::endl;
        //Develop your LBU instr implementation here
            break;

            //LHU : Load Half Unsigned
            case lhu_funct3: std::cout << "LHU instruction Detected" << std::endl;
        //Develop your LHU instr implementation here
            break;
        }
    break;

    case 0x67:  // i type 0x67
        switch(funct3){
            //JALR : Jump & Link Register
            case jalr_funct3: std::cout << "JALR instruction Detected" << std::endl;
        //Develop your LB instr implementation here
            break;
            }
    break;

    case 0x73:  // i type 0x73
        switch(funct3){
            //ECALL and EBREAK : 
            case ecall_ebreak_funct3: 
                switch(i_imm){
                case 0x0: std::cout << "ECALL instruction Detected" << std::endl;
            //Develop your ECALL instr implementation here
                break;

                case 0x1: std::cout << "EBREAK instruction Detected" << std::endl;
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
                          std::cout << "BEQ instruction Detected" << std::endl;
                            if(r[rs1] == r[rs2])
                                c_pc = u_imm;
            break;

            //BNE : Branch if Not Equal
            case bne_funct3: std::cout << "BNE instruction Detected" << std::endl;
        //Develop your BNE instr implementation here
            break;

            //BLT : Branch if Less Than
            case blt_funct3: std::cout << "BLT instruction Detected" << std::endl;
        //Develop your BLT instr implementation here
            break;

            //BGE : Branch if Greater than or Equal 
            case bge_funct3: std::cout << "BGE instruction Detected" << std::endl;
        //Develop your BGE instr implementation here
            break;
        
            //BLTU : Branch if Less Than Unsigned
            case bltu_funct3: std::cout << "BLTU instruction Detected" << std::endl;
        //Develop your BLTU instr implementation here
            break;
        
            //BGE : Branch if Greater than or Equal Unsigned
            case bgeu_funct3: std::cout << "BGEU instruction Detected" << std::endl;
        //Develop your BGEU instr implementation here
            break;
        }
    break;

    //LUI: Load Upper Immediate 
    case 0x37: 
                std::cout << "LUI instruction Detected" << std::endl;
                r[rd] = u_imm;
                std::cout << "LUI Result:\t" << std::hex << r[rd] << "\n" << std::endl;
    break;

    //AUIPC: Add Upper Immediate to PC
    case 0x17: 
                std::cout << "AUIPC instruction Detected" << std::endl;
                r[rd] = c_pc + u_imm;           //20 and lower 12 zero
                std::cout << "AUIPC Result:\t" << std::hex << r[rd] << "\n" << std::endl;
    break;

    //JAL : Jump and Link
    case j_type_opcode: std::cout << "JAL instruction Detected" << std::endl;
    //Develop your JAL instr implementation here
    break;
    }

    std::cout << "Register values are:" << std::endl;
    int reg_elements = 0;
    for (int i = reg_elements; i <= 31; i++){
        std::cout << i << ":" << std::uppercase << std::hex << r[i] << "\t";
    }
    std::cout << "\n" << std::endl;

}