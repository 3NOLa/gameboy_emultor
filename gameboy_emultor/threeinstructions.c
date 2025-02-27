#include "threeinstructions.h"

void add_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint16_t result = regs->A + value;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF)) > 0xF);
	setflag(regs, FLAG_C, result > 0xFF);

	regs->A = (uint8_t)result;
}

void adc_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A + value + carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF) + carry) > 0xF);
	setflag(regs, FLAG_C, result > 0xFF);

	regs->A = (uint8_t)result;
}

void sub_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint16_t result = regs->A - value;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, (regs->A & 0xF) < (value & 0xF));
	setflag(regs, FLAG_C, regs->A < value);

	regs->A = (uint8_t)result;
}

void sbc_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A - value - carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, ((regs->A & 0xF) < ((value & 0xF) + carry)));
	setflag(regs, FLAG_C, regs->A < (value + carry));

	regs->A = (uint8_t)result;
}

void xor_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	regs->A ^= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void or_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	regs->A |= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void cp_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t result = regs->A - value;

	setflag(regs, FLAG_Z, result == 0);          // Zero flag: Set if A == value
	setflag(regs, FLAG_N, 1);                    // Subtraction flag: Always set
	setflag(regs, FLAG_H, ((regs->A & 0xF) - (value & 0xF)) < 0); // Half-carry flag
	setflag(regs, FLAG_C, regs->A < value);      // Carry flag: Set if borrow occurs
}

void group_33_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
	switch (opcode & 0x3F)
	{
	case 0x6: add_a_imm8(regs, memory); break;
	case 0xE: adc_a_imm8(regs, memory); break;
	case 0x16: sub_a_imm8(regs, memory); break;
	case 0x1E: sbc_a_imm8(regs, memory); break;
	case 0x26: and_a_imm8(regs, memory); break;
	case 0x2E: xor_a_imm8(regs, memory); break; 
	case 0x36: or_a_imm8(regs, memory); break;
	case 0x3E: cp_a_imm8(regs, memory); break;

	default:
		break;
	}
}