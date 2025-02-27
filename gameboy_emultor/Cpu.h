#include "Memory.h"
#include "registers.h"

typedef struct CPU
{
	membus bus;
	uint16_t pc;
	registers regs;
}cpu, *cptr;

