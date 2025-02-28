#include "zeroinstructions.h"
void inc_r16(uint16_t* reg) {
    (*reg)++;
}

void dec_r16(uint16_t* reg) {
    (*reg)--;
}

void inc_r8(uint8_t* reg) {
    (*reg)++;
}

void dec_r8(uint8_t* reg) {
    (*reg)--;
}

void add_hl_r16(regptr regs, uint16_t* reg) {
    uint32_t result = regs->HL + *reg;

    setflag(regs, FLAG_N, 0); /* Reset N flag */
    setflag(regs, FLAG_H, ((regs->HL & 0x0FFF) + (*reg & 0x0FFF)) > 0x0FFF); /* Half carry */
    setflag(regs, FLAG_C, result > 0xFFFF); /* Carry flag */

    regs->HL = (uint16_t)result;
}

/* Load value at address pointed to by 16-bit register into A */
void ld_a_r16mem(regptr regs, uint8_t* memory, uint16_t* r16) {
    regs->A = memory[*r16];
}

void ld_r16mem_a(regptr regs, uint8_t* memory, uint16_t* r16) {
    memory[*r16] = regs->A;
}

void ld_r16_imm16(regptr regs, uint8_t* memory, uint16_t* r16) {
    uint8_t low = memory[regs->PC + 1];
    uint8_t high = memory[regs->PC + 2];
    regs->PC += 2;

    *r16 = (high << 8) | low;
}

void ld_imm16_sp(regptr regs, uint8_t* memory) {
    uint8_t low = memory[regs->PC + 1];
    uint8_t high = memory[regs->PC + 2];
    regs->PC += 2;

    memory[(high << 8) | low] = regs->SP;
}

void ld_r8_imm8(regptr regs, uint8_t* memory, uint16_t* r8) {
    uint8_t byte = memory[++regs->PC];
    *r8 = byte;
}

void jr(regptr regs, uint8_t* memory) {
    regs->PC += memory[regs->PC + 1]; // Signed 8-bit relative jump
}

void jr_cond(regptr regs, uint8_t* memory, uint8_t condition) {
    if (condition) {
        regs->PC += memory[regs->PC + 1];
    }
}

int zero_fourbit_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
    int status = 1;

    switch (opcode & 0xf)
    {
    case 0x0: break;
    case 0x1: ld_r16_imm16(regs, memory, r16_adr(regs, (opcode >> 4) & 0x3)); break;
    case 0x3: inc_r16(r16_adr(regs, (opcode >> 4) & 0x3)); break;
    case 0x2: ld_imm16_a(regs, memory, r16_adr(regs, (opcode >> 4) & 0x3)); break;
    case 0x8: ld_imm16_sp(regs, memory); break;
    case 0x9: add_hl_r16(regs, r16_adr(regs, (opcode >> 4) & 0x3)); break;
    case 0xA: ld_a_imm16(regs, memory, r16_adr(regs, (opcode >> 4) & 0x3)); break;
    case 0xB: dec_r16(r16_adr(regs, (opcode >> 4) & 0x3)); break;
    default:
        status = 0;
        break;
    }

    return status;
}

int zero_threebit_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
    int status = 1;

    switch (opcode & 0x7)
    {
    case 0x0:
        if ((opcode >> 5) == 0) jr(regs, memory);
        else jr_cond(regs, memory, (opcode >> 3) & 3);
        break;
    case 0x4: inc_r8(r8_adr(regs, memory, (opcode >> 3) & 0x7)); break;
    case 0x5: dec_r8(r8_adr(regs, memory, (opcode >> 3) & 0x7)); break;
    case 0x6: ld_r8_imm8(regs, memory, r8_adr(regs, memory, (opcode >> 3) & 0x7)); break;
    case 0x7: 
    {
        switch ((opcode >> 3) & 0x7)
        {
        case 0x0: rlca(regs); break;
        case 0x1: rrca(regs); break;
        case 0x2: rla(regs); break;
        case 0x3: rra(regs); break;
        case 0x4: daa(regs); break;
        case 0x5: cpl(regs); break;
        case 0x6: scf(regs); break;
        case 0x7: ccf(regs); break;
        }
    }
    default:
        status = 0;
        break;
    }

    return status;
}

void stop(regptr regs) {
    regs->PC += 2;
    //printf("CPU Stopped! Waiting for input...\n");
    //emulator_paused = 1; 
}

void group_00_instructions(regptr regs, uint8_t* memory, uint8_t opcode) {
    if (opcode == 0x00) {
        // NOP (No Operation)
        return;
    }
    else if (opcode == 0x10) {
        stop(regs);
        return;
    }

    int status = zero_fourbit_instructions(regs, memory, opcode);

    if (!status)
        status = zero_threebit_instructions(regs, memory, opcode);

    if (!status);
       // printf("Error: Unknown opcode: 0x%02X\n", opcode);
}
