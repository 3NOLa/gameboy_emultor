#include "registers.h"
#include "flags.h"

void ldh_c_a(regptr regs, uint8_t* memory);
void ldh_imm8_a(regptr regs, uint8_t* memory);
void ld_imm16_a(regptr regs, uint8_t* memory);
void ldh_a_c(regptr regs, uint8_t* memory);
void ldh_a_imm8(regptr regs, uint8_t* memory);
void ld_a_imm16(regptr regs, uint8_t* memory);
