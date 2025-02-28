#pragma once
#include "registers.h"
#include "flags.h"


void add_a_r8(regptr regs, uint8_t* r8);
void adc_a_r8(regptr regs, uint8_t* r8);
void sub_a_r8(regptr regs, uint8_t* r8);
void sbc_a_r8(regptr regs, uint8_t* r8);
void and_a_r8(regptr regs, uint8_t* r8);
void xor_a_r8(regptr regs, uint8_t* r8);
void or_a_r8(regptr regs, uint8_t* r8);
void cp_a_r8(regptr regs, uint8_t* r8);
void group_22_instructions(regptr regs, uint8_t* memory, uint8_t opcode);


