#include "ioinstructions.h"
#include "memory.h"

void ldh_c_a(regptr regs, uint8_t* memory)
{
	uint8_t value = regs->A;
	memory[IO_REGS_START + regs->C] = value;
}

void ldh_imm8_a(regptr regs, uint8_t* memory)
{
	uint8_t value = regs->A;
	uint8_t mem = memory[++regs->PC];
	memory[IO_REGS_START + mem] = value;
}

void ld_imm16_a(regptr regs, uint8_t* memory)
{
	uint8_t value = regs->A;
	uint8_t low_byte = memory[++regs->PC];
	uint8_t high_byte = memory[++regs->PC];
	uint16_t address = (high_byte << 8) | low_byte; 
	memory[IO_REGS_START + address] = value;  
}


void ldh_a_c(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[IO_REGS_START + regs->C];
	regs->A = value;
}

void ldh_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t mem = memory[++regs->PC];  // Read the immediate 8-bit value
	uint8_t value = memory[IO_REGS_START + mem];  // Load value from the address $FF00 + mem
	regs->A = value;  // Store the value in A
}

void ld_a_imm16(regptr regs, uint8_t* memory)
{
	uint8_t low_byte = memory[++regs->PC];
	uint8_t high_byte = memory[++regs->PC];
	uint16_t address = (high_byte << 8) | low_byte;  
	regs->A = memory[address]; 
}

