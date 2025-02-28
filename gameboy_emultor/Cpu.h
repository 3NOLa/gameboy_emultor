#pragma once
#include "Memory.h"
#include "flags.h"
#include "cb_prefix_instructions.h"
#include "twoinstructions.h"
#include "zeroinstructions.h"
#include "threeinstructions.h"
#include "stackfunctions.h"
#include "oneinstructions.h"
#include "oneinstructions.h"


typedef struct CPU
{
	membus bus;
	uint16_t pc;
	registers regs;
}cpu, *cptr;

