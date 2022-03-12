#ifndef __CURRENT_INSTR_H__
#define __CURRENT_INSTR_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include "commondefs.h"
#include "fileparse.h"
#include "isasim.h"
#include "request.h"

class current_instr{ 
    public:
    explicit current_instr(uint64_t& pc, uint64_t& sp, std::ofstream& current_instr_reg):
    c_pc(pc), c_sp(sp), current_instr_reg_file(current_instr_reg) 
    {
        c_instr = (uint32_t)memory_array[c_pc] | (uint32_t)(memory_array[c_pc + 1] << 8) | (uint32_t)(memory_array[c_pc + 2] << 16) | (uint32_t)(memory_array[c_pc + 3] << 24);
        opcode = c_instr & (0x7F);
        funct7 = (c_instr & (0xFE000000)) >> 25;
        funct3 = (c_instr & (0x7000)) >> 12;
        rd = (c_instr & (0xF80)) >> 7;
        rs1 = (c_instr & (0xF8000)) >> 15;
        rs2 = (c_instr & (0x1F00000)) >> 20;

        i_imm = (c_instr & (0xFFF00000)) >> 20;
        s_imm = ((c_instr & (0xF80)) >> 7) | ((c_instr & (0xFE000000)) >> 20);
        b_imm = ((c_instr & (0x80000000)) >> 19) | ((c_instr & (0x80)) << 4) | ((c_instr & (0x7E000000)) >> 20) | ((c_instr & (0xF00)) >> 7) | 0x0;
        u_imm = ((c_instr & (0xFFFFF000)) >> 12);
        j_imm = ((c_instr & (0x80000000)) >> 11) | (c_instr & (0xFF000)) | ((c_instr & (0x100000)) >> 9) | ((c_instr & (0x7FE00000)) >> 20) | 0x0;
    }
    
    // Current instruction and sp and pc for the same  
    uint64_t& c_pc;
    uint64_t& c_sp;
    uint32_t c_instr;

    // Output filestream
    std::ofstream& current_instr_reg_file;

    // Instruction field constants 
    uint8_t opcode;
    // Opcode constants
    static constexpr uint8_t r_type_opcode = 0x33;
    static constexpr std::array<uint8_t, 4> i_type_opcode {0x13, 0x3, 0x73, 0x67};
    static constexpr uint8_t s_type_opcode = 0x23;
    static constexpr uint8_t b_type_opcode = 0x63;
    static constexpr std::array<uint8_t, 2> u_type_opcode = {0x37, 0x17};
    static constexpr uint8_t j_type_opcode = 0x6F;

    uint8_t funct7;
    // Funct7 constants
    static constexpr uint8_t add_funct7  = 0x00;
    static constexpr uint8_t xor_funct7  = 0x00;
    static constexpr uint8_t or_funct7   = 0x00;
    static constexpr uint8_t and_funct7  = 0x00;
    static constexpr uint8_t sll_funct7  = 0x00;
    static constexpr uint8_t srl_funct7  = 0x00;
    static constexpr uint8_t slt_funct7  = 0x00;
    static constexpr uint8_t sltu_funct7 = 0x00;
    static constexpr uint8_t srli_funct7 = 0x00;
    static constexpr uint8_t rv32m_funct7= 0x01;
    static constexpr uint8_t sub_funct7  = 0x20;
    static constexpr uint8_t sra_funct7  = 0x20;
    static constexpr uint8_t srai_funct7 = 0x20;

    uint8_t funct3;
    // Funct3 constants
    static constexpr uint8_t add_funct3  = 0x0;
    static constexpr uint8_t addi_funct3 = 0x0;
    static constexpr uint8_t sub_funct3  = 0x0;
    static constexpr uint8_t beq_funct3  = 0x0;
    static constexpr uint8_t lb_funct3   = 0x0;
    static constexpr uint8_t jalr_funct3 = 0x0;
    static constexpr uint8_t sb_funct3   = 0x0;
    static constexpr uint8_t ecall_ebreak_funct3 = 0x0;
    static constexpr uint8_t sll_funct3  = 0x1;
    static constexpr uint8_t slli_funct3 = 0x1;
    static constexpr uint8_t bne_funct3  = 0x1;
    static constexpr uint8_t lh_funct3   = 0x1;
    static constexpr uint8_t sh_funct3   = 0x1;
    static constexpr uint8_t slt_funct3  = 0x2;
    static constexpr uint8_t slti_funct3 = 0x2;
    static constexpr uint8_t lw_funct3   = 0x2;
    static constexpr uint8_t sw_funct3   = 0x2;
    static constexpr uint8_t sltu_funct3 = 0x3;
    static constexpr uint8_t sltiu_funct3= 0x3;
    static constexpr uint8_t sd_funct3   = 0x3;
    static constexpr uint8_t xor_funct3  = 0x4;
    static constexpr uint8_t xori_funct3 = 0x4;
    static constexpr uint8_t blt_funct3  = 0x4;
    static constexpr uint8_t lbu_funct3  = 0x4;
    static constexpr uint8_t srl_funct3  = 0x5;
    static constexpr uint8_t srli_srai_funct3 = 0x5;
    static constexpr uint8_t sra_funct3  = 0x5;    
    static constexpr uint8_t bge_funct3  = 0x5;
    static constexpr uint8_t lhu_funct3  = 0x5; 
    static constexpr uint8_t or_funct3   = 0x6;
    static constexpr uint8_t ori_funct3  = 0x6;    
    static constexpr uint8_t bltu_funct3 = 0x6;
    static constexpr uint8_t and_funct3  = 0x7;
    static constexpr uint8_t andi_funct3 = 0x7;
    static constexpr uint8_t bgeu_funct3 = 0x7;

    // RV32M Extra Credit Implementation
    static constexpr uint8_t mul_funct3    = 0x0;
    static constexpr uint8_t mulh_funct3   = 0x1;
    static constexpr uint8_t mulhu_funct3  = 0x2;
    static constexpr uint8_t mulhsu_funct3 = 0x3;
    static constexpr uint8_t div_funct3    = 0x4;
    static constexpr uint8_t divu_funct3   = 0x5;
    static constexpr uint8_t rem_funct3    = 0x6;
    static constexpr uint8_t remu_funct3   = 0x7;

    // Register decoding
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;

    // Immediate values masking and decoding for each type of instr
    uint32_t i_imm;
    uint32_t s_imm;
    uint32_t b_imm;
    uint32_t u_imm;
    uint32_t j_imm;

    // Get current Instruction type (Do we even need this??)
    uint8_t get_instr_type(uint8_t opcode);

    // Get Register Values
    uint32_t get_rd_value(uint32_t r[]);
    uint32_t get_rs1_value(uint32_t r[]);
    uint32_t get_rs2_value(uint8_t rs2);

    // Get Signed Values of imm fields
    int32_t get_signed_i_imm(uint32_t i_imm);
    int32_t get_signed_s_imm(uint32_t s_imm);
    int32_t get_signed_b_imm(uint32_t b_imm);
    int32_t get_signed_j_imm(uint32_t j_imm);

    // Instruction Execution logic
    void instr_execution(uint32_t r[]);

    //prints detected instruction
    void print_instr(std::string str);

    //function to get exponential power
    uint64_t get_power (uint64_t base, uint64_t exponent);

};
#endif