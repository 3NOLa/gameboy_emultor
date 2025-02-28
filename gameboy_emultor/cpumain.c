#include "cpu.h"

void cpu_execute(cptr cpu) {
    regptr regs = &(cpu->regs);
    uint8_t* memory = ((cpu->bus).memory);

    uint8_t opcode = memory[regs->PC++];

    // Handle main opcodes
    if (opcode == 0xCB) {//Prefix	1	1	0	0	1	0	1	1
        // Handle CB prefixed instructions
        opcode = memory[regs->PC++];
        execute_cb_instruction(regs, memory, opcode);
    }
    else {
        switch (opcode & 0xC0) {
        case 0x00: group_00_instructions(regs, memory, opcode); break;
        case 0x40: group_11_instructions(regs, memory, opcode); break;
        case 0x80: group_22_instructions(regs, memory, opcode); break;
        case 0xC0: group_33_instructions(regs, memory, opcode); break;
        }
    }

    if (regs->IME_enable_delay > 1) {
        regs->IME = 1;  // Enable IME
        regs->IME_enable_delay = 0;  // Clear the delay flag
    }
    else if(regs->IME_enable_delay == 1) regs->IME_enable_delay++;
}