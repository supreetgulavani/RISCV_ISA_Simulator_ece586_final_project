#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"

/*
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
        switch(funct7){
        case 0x00:
            switch(funct3){
            case add_funct3: std::cout << "yay! r type add" << std::endl;
            //Develop your ADD instr implementation here
            break;

            case xor_funct3: std::cout << "yay! r type xor" << std::endl;
            //Develop your XOR instr implementation here
            break;

            case or_funct3: std::cout << "yay! r type or" << std::endl;
            //Develop your OR instr implementation here
            break;

            case and_funct3: std::cout << "yay! r type and" << std::endl;
            //Develop your AND instr implementation here
            break;

            case sll_funct3: std::cout << "yay! r type sll" << std::endl;
            //Develop your SLL instr implementation here
            break;

            case srl_funct3: std::cout << "yay! r type srl" << std::endl;
            //Develop your SRL instr implementation here
            break;

            case slt_funct3: std::cout << "yay! r type slt" << std::endl;
            //Develop your SLT instr implementation here
            break;

            case sltu_funct3: std::cout << "yay! r type sltu" << std::endl;
            //Develop your SLTU instr implementation here
            break;
            }
        break;

        case 0x20:
            switch(funct3){
            case sub_funct3: std::cout << "yay! r type sub" << std::endl;
            //Develop your SUB instr implementation here
            break;

            case sra_funct3: std::cout << "yay! r type sra" << std::endl;
            //Develop your SRA instr implementation here
            break;
            }
        break;
        }
    break;

    case 0x13:  // i type 0x13
        switch(funct3){
        case addi_funct3: std::cout << "yay! i type addi" << std::endl;
        r[rd] = r[rs1] + i_imm;
        //Develop your ADDI instr implementation here
        break;

        case xori_funct3: std::cout << "yay! i type xori" << std::endl;
        //Develop your XORI instr implementation here
        break;

        case ori_funct3: std::cout << "yay! i type ori" << std::endl;
        //Develop your ORI instr implementation here
        break;

        case andi_funct3: std::cout << "yay! i type andi" << std::endl;
        //Develop your ANDI instr implementation here
        break;

        case slli_funct3: std::cout << "yay! i type slli" << std::endl;
        //Develop your SLLI instr implementation here
        break;

        case srli_srai_funct3: std::cout << "yay! i type srli" << std::endl;
        //Develop your SRLI instr implementation here
        break;

        case slti_funct3: std::cout << "yay! i type slti" << std::endl;
        //Develop your SLTI instr implementation here
        break;

        case sltiu_funct3: std::cout << "yay! i type sltiu" << std::endl;
        //Develop your SLTIU instr implementation here
        break;
        }
    break;

    case 0x3:  // i type 0x3
        switch(funct3){
        case lb_funct3: std::cout << "yay! i type lb" << std::endl;
        //Develop your LB instr implementation here
        break;

        case lh_funct3: std::cout << "yay! i type lh" << std::endl;
        //Develop your LH instr implementation here
        break;

        case lw_funct3: std::cout << "yay! i type lw" << std::endl;
        //Develop your LW instr implementation here
        break;

        case lbu_funct3: std::cout << "yay! i type lbu" << std::endl;
        //Develop your LBU instr implementation here
        break;

        case lhu_funct3: std::cout << "yay! i type lhu" << std::endl;
        //Develop your LHU instr implementation here
        break;
        }
    break;

    case 0x67:  // i type 0x67
        switch(funct3){
        case jalr_funct3: std::cout << "yay! i type jalr" << std::endl;
        //Develop your LB instr implementation here
        break;
        }
    break;

    case 0x73:  // i type 0x73
        switch(funct3){
        case ecall_ebreak_funct3: 
            switch(i_imm){
            case 0x0: std::cout << "yay! i type ecall" << std::endl;
            //Develop your ECALL instr implementation here
            break;

            case 0x1: std::cout << "yay! i type ebreak" << std::endl;
            //Develop your EBREAK instr implementation here
            break;
            }
        break;    
        }
   
    break;

    case b_type_opcode:
        switch(funct3){
        case beq_funct3: std::cout << "yay! b type beq" << std::endl;
        //Develop your BEQ instr implementation here
        break;

        case bne_funct3: std::cout << "yay! b type bne" << std::endl;
        //Develop your BNE instr implementation here
        break;

        case blt_funct3: std::cout << "yay! b type blt" << std::endl;
        //Develop your BLT instr implementation here
        break;

        case bge_funct3: std::cout << "yay! b type bge" << std::endl;
        //Develop your BGE instr implementation here
        break;
        
        case bltu_funct3: std::cout << "yay! b type bltu" << std::endl;
        //Develop your BLTU instr implementation here
        break;
        
        case bgeu_funct3: std::cout << "yay! b type bgeu" << std::endl;
        //Develop your BGEU instr implementation here
        break;
        }
    break;

    //u type 0x37
    case 0x37: std::cout << "yay! u type lui" << std::endl;
    //Develop your LUI instr implementation here
    break;

    //u type 0x17
    case 0x17: std::cout << "yay! u type auipc" << std::endl;
    //Develop your AUIPC instr implementation here
    break;

    case j_type_opcode: std::cout << "yay! j type jal" << std::endl;
    //Develop your JAL instr implementation here
    break;
    }

    std::cout << "register values are:" << std::endl;
    int reg_elements = 0;
    for (int i = reg_elements; i <= 31; i++){
        std::cout << i << ":" << std::uppercase << std::hex << (int)r[i] << "\t";
    }
    std::cout << std::endl;

}