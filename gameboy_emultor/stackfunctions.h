#pragma once
#include "registers.h"
#include "flags.h"

void push(regptr regs, uint8_t* memory, uint16_t value);
uint16_t pop(regptr regs, uint8_t* memory);
void pop_r16stk(regptr regs, uint8_t* memory, uint8_t opcode);
void push_r16stk(regptr regs, uint8_t* memory, uint8_t opcode);
void ret(regptr regs, uint8_t* memory);
void ei(regptr regs);
void di(regptr regs);
void reti(regptr regs, uint8_t* memory);
void ret_nz(regptr regs, uint8_t* memory);
void ret_z(regptr regs, uint8_t* memory);
void ret_nc(regptr regs, uint8_t* memory);
void ret_c(regptr regs, uint8_t* memory);
void ret_cond(regptr regs, uint8_t* memory, uint8_t opcode);
void jp_imm16(regptr regs, uint8_t* memory);
void jp_hl(regptr regs, uint8_t* memory);
void jp_nz(regptr regs, uint8_t* memory);
void jp_z(regptr regs, uint8_t* memory);
void jp_nc(regptr regs, uint8_t* memory);
void jp_c(regptr regs, uint8_t* memory);
void jp_cond(regptr regs, uint8_t* memory, uint8_t opcode);
void call_imm16(regptr regs, uint8_t* memory);
void call_nz(regptr regs, uint8_t* memory);
void call_z(regptr regs, uint8_t* memory);
void call_nc(regptr regs, uint8_t* memory);
void call_c(regptr regs, uint8_t* memory);
void call_cond(regptr regs, uint8_t* memory, uint8_t opcode);
void add_sp_imm8(regptr regs, uint8_t* memory);
void ld_sp_hl(regptr regs, uint8_t* memory);
void ld_hl_sp_imm8(regptr regs, uint8_t* memory);
void rst_tgt3(regptr regs, uint8_t* memory);
void rst_tgt2(regptr regs, uint8_t* memory);
void rst_tgt1(regptr regs, uint8_t* memory);
void rst_tgt0(regptr regs, uint8_t* memory);