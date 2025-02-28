#pragma once
#include "registers.h"
#include "flags.h"

void inc_r16(uint16_t* reg);
void dec_r16(uint16_t* reg);
void inc_r8(uint8_t* reg);
void dec_r8(uint8_t* reg);
void add_hl_r16(regptr regs, uint16_t* reg);
void ld_a_r16mem(regptr regs, uint8_t* memory, uint16_t* r16);
void ld_r16mem_a(regptr regs, uint8_t* memory, uint16_t* r16);
void ld_r16_imm16(regptr regs, uint8_t* memory, uint16_t* r16);
void ld_imm16_sp(regptr regs, uint8_t* memory);
void ld_r8_imm8(regptr regs, uint8_t* memory, uint16_t* r8);
void jr(regptr regs, uint8_t* memory);
void jr_cond(regptr regs, uint8_t* memory, uint8_t condition);
void group_00_instructions(regptr regs, uint8_t* memory, uint8_t opcode);