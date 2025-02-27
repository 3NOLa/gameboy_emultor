#include "registers.h"
#include "flags.h"

uint16_t pop(regptr regs, uint8_t* memory);
void push(regptr regs, uint8_t* memory, uint16_t value);