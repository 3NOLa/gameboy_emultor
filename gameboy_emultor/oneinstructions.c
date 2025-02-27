#include "oneinstructions.h"

void group_11_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
	if (opcode == 0x76)//halt
	{
		
	}
	else
	{
		uint8_t* destr8 = r8_adr(regs,memory,(opcode >> 3) & 7);
		uint8_t* sourcer8 = r8_adr(regs, memory, (opcode & 7));

		*destr8 = *sourcer8;
	}
}