#include "Gpu.h"

#define MEMORY_SIZE 0xFFFF
#define IO_REGS_START  0xFF00
#define INTERRUPT_FLAG 0xFF0F
#define INTERRUPT_ENABLE 0xFFFF

typedef struct MemoryBus
{
	uint8_t memory[MEMORY_SIZE];
	gpu g;
}membus, *memptr;