#include "twoinstructions.h"

void add_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	uint16_t result = regs->A + value;  

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);   
	setflag(regs, FLAG_N, 0);                     
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF)) > 0xF); 
	setflag(regs, FLAG_C, result > 0xFF);          

	regs->A = (uint8_t)result;  
}

void adc_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A + value + carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF) + carry) > 0xF);
	setflag(regs, FLAG_C, result > 0xFF);

	regs->A = (uint8_t)result;
}

void sub_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	uint16_t result = regs->A - value;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, (regs->A & 0xF) < (value & 0xF));
	setflag(regs, FLAG_C, regs->A < value);

	regs->A = (uint8_t)result;
}

void sbc_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A - value - carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, ((regs->A & 0xF) < ((value & 0xF) + carry)));
	setflag(regs, FLAG_C, regs->A < (value + carry));

	regs->A = (uint8_t)result;
}

void xor_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	regs->A ^= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void or_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	regs->A |= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void cp_a_r8(regptr regs, uint8_t* r8)
{
	uint8_t value = *r8;
	uint8_t result = regs->A - value;

	setflag(regs, FLAG_Z, result == 0);          // Zero flag: Set if A == value
	setflag(regs, FLAG_N, 1);                    // Subtraction flag: Always set
	setflag(regs, FLAG_H, ((regs->A & 0xF) - (value & 0xF)) < 0); // Half-carry flag
	setflag(regs, FLAG_C, regs->A < value);      // Carry flag: Set if borrow occurs
}

void group_22_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
	uint8_t* r8 = r8_adr(regs, memory, opcode & 7);
	
	switch ((opcode >> 3) & 7)
	{
	case 0x0: add_a_r8(regs, r8);
	case 0x1: adc_a_r8(regs, r8);
	case 0x2: sub_a_r8(regs, r8);
	case 0x3: sbc_a_r8(regs, r8);
	case 0x4: and_a_r8(regs, r8);
	case 0x5: xor_a_r8(regs, r8);
	case 0x6: or_a_r8(regs, r8);
	case 0x7: cp_a_r8(regs, r8);

	default:
		break;
	}
}