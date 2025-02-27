#include "registers.h"
#include "flags.h"

void rlc_r8(regptr regs, uint8_t* r8);
void rrc_r8(regptr regs, uint8_t* r8);
void rl_r8(regptr regs, uint8_t* r8);
void rr_r8(regptr regs, uint8_t* r8);
void sla_r8(regptr regs, uint8_t* r8);
void sra_r8(regptr regs, uint8_t* r8);
void swap_r8(regptr regs, uint8_t* r8);
void srl_r8(regptr regs, uint8_t* r8);
void bit_b3_r8(regptr regs, uint8_t* r8);
void res_b3_r8(regptr regs, uint8_t* r8);
void set_b3_r8(regptr regs, uint8_t* r8);
