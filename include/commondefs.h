#ifndef __COMMONDEF_H__
#define __COMMONDEF_H__

#include <ostream>

struct nxt_instr_struct {
    uint64_t program_counter;
    uint64_t stack_pointer;
    uint64_t return_addr;

    uint32_t reg [31];
};

#endif