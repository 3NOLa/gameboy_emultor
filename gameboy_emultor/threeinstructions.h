#pragma once
#include "registers.h"
#include "flags.h"
#include "stackfunctions.h"
#include "ioinstructions.h"

void add_a_imm8(regptr regs, uint8_t* memory);
void adc_a_imm8(regptr regs, uint8_t* memory);
void sub_a_imm8(regptr regs, uint8_t* memory);
void sbc_a_imm8(regptr regs, uint8_t* memory);
void and_a_imm8(regptr regs, uint8_t* memory);
void xor_a_imm8(regptr regs, uint8_t* memory);
void or_a_imm8(regptr regs, uint8_t* memory);
void cp_a_imm8(regptr regs, uint8_t* memory);
void group_33_instructions(regptr regs, uint8_t* memory, uint8_t opcode);


