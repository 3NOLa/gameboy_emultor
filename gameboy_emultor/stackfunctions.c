#include "stackfunctions.h"

void push(regptr regs, uint8_t* memory, uint16_t value) {
	regs->SP -= 2; // Stack grows downward
	memory[regs->SP] = value & 0xFF;        // Lower byte
	memory[regs->SP + 1] = (value >> 8);    // Upper byte
}

uint16_t pop(regptr regs, uint8_t* memory) {
	uint16_t value = memory[regs->SP] | (memory[regs->SP + 1] << 8);
	regs->SP += 2; // Stack shrinks upward
	return value;
}

void  pop_r16stk(regptr regs, uint8_t* memory,uint8_t opcode)
{
	uint16_t* reg = r16_adr(regs, (opcode >> 4) & 2);
	uint16_t value = memory[regs->SP] | (memory[regs->SP + 1] << 8);
	regs->SP += 2;
	*reg = value;
}

void push_r16stk(regptr regs, uint8_t* memory, uint8_t opcode)
{
	uint16_t* reg = r16_adr(regs, (opcode >> 4) & 2);
	uint16_t value = *reg;
	regs->SP -= 2; 
	memory[regs->SP] = value & 0xFF;        
	memory[regs->SP + 1] = (value >> 8);    
}

void ret(regptr regs, uint8_t* memory)
{
	uint16_t adr = pop(regs, memory);
	regs->PC = adr;
}

void ret_nz(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_Z))
		ret(regs, memory);
}

void ret_z(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_Z))
		ret(regs, memory);
}

void ret_nc(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_C))
		ret(regs, memory);
}

void ret_c(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_C))
		ret(regs, memory);
}

void ret_nz(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_Z))
		ret(regs, memory);
}

void ret_cond(regptr regs, uint8_t* memory, uint8_t opcode)
{
	switch ((opcode >> 3) & 2)
	{
	case 0x0:ret_nz(regs, memory);
	case 0x1:ret_z(regs, memory);
	case 0x2:ret_nc(regs, memory);
	case 0x3:ret_c(regs, memory);
	default:
		break;
	}
}

void jp_imm16(regptr regs, uint8_t* memory)
{
	uint16_t addr = memory[regs->PC + 1] | (memory[regs->PC + 2] << 8);
	regs->PC = addr;
}

void jp_hl(regptr regs, uint8_t* memory)
{
	regs->PC = regs->HL;
}


void jp_nz(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_Z))
		jp_imm16(regs, memory);
}

void jp_z(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_Z))
		jp_imm16(regs, memory);
}

void jp_nc(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_C))
		jp_imm16(regs, memory);
}

void jp_c(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_C))
		jp_imm16(regs, memory);
}

void jp_cond(regptr regs, uint8_t* memory, uint8_t opcode)
{
	switch ((opcode >> 3) & 2)
	{
	case 0x0:jp_nz(regs, memory);
	case 0x1:jp_z(regs, memory);
	case 0x2:jp_nc(regs, memory);
	case 0x3:jp_c(regs, memory);
	default:
		break;
	}
}

void call_imm16(regptr regs, uint8_t* memory)
{
	uint16_t addr = memory[regs->PC+1] | (memory[regs->PC + 2] << 8);
	regs->SP -= 2;
	memory[regs->SP] = regs->PC >> 8;
	memory[regs->SP + 1] = regs->PC & 0xff;
	regs->PC = addr;
}

void call_nz(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_Z))
		call_imm16(regs, memory);
}

void call_z(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_Z))
		call_imm16(regs, memory);
}

void call_nc(regptr regs, uint8_t* memory)
{
	if (!getFlag(regs, FLAG_C))
		call_imm16(regs, memory);
}

void call_c(regptr regs, uint8_t* memory)
{
	if (getFlag(regs, FLAG_C))
		call_imm16(regs, memory);
}

void call_cond(regptr regs, uint8_t* memory, uint8_t opcode)
{
	switch ((opcode >> 3) & 2)
	{
	case 0x0:call_nz(regs, memory);
	case 0x1:call_z(regs, memory);
	case 0x2:call_nc(regs, memory);
	case 0x3:call_c(regs, memory);
	default:
		break;
	}
}

void add_sp_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[regs->PC + 1];
	regs->SP += value;
}

void ld_sp_hl(regptr regs, uint8_t* memory)
{
	uint8_t value = regs->HL;
	regs->SP = value;
}

void ld_hl_sp_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[regs->PC + 1];
	value += regs->SP;
	regs->HL = value;
}