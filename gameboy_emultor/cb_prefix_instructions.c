#include "cb_prefix_instructions.h"

void rlc_r8(regptr regs, uint8_t* r8)
{
    uint8_t mostbit = *r8 & 0x80;
    *r8 = ((*r8 << 1) | (*r8 >> 7));

    setflag(regs, FLAG_C, (mostbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

void rrc_r8(regptr regs, uint8_t* r8)
{
    uint8_t leastbit = *r8 & 0x1;
    *r8 = ((*r8 >> 1) | (*r8 << 7));

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

void rl_r8(regptr regs, uint8_t* r8)
{
    uint8_t mostbit = *r8 & 0x80;
    uint8_t carry = getFlag(regs, FLAG_C);

    *r8 = (*r8 << 1) | carry;

    setflag(regs, FLAG_C, (mostbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

void rr_r8(regptr regs, uint8_t* r8)
{
    uint8_t leastbit = *r8 & 0x1;
    uint8_t carry = getFlag(regs, FLAG_C);

    *r8 = (*r8 >> 1) | (carry << 7);

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

void swap_r8(regptr regs, uint8_t* r8)
{
    *r8 = ((*r8 >> 4) | (*r8 << 4));

    setflag(regs, FLAG_Z, (*r8 == 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_C, 0);
}

void bit_b3_r8(regptr regs, uint8_t* r8, uint8_t bit)
{
    setflag(regs, FLAG_Z, ((*r8 & (1 << bit)) == 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 1);
}

void res_b3_r8(regptr regs, uint8_t* r8, uint8_t bit)
{
    *r8 &= ~(1 << bit);
}

void set_b3_r8(regptr regs, uint8_t* r8, uint8_t bit)
{
    *r8 |= (1 << bit);
}

void sla_r8(regptr regs, uint8_t* r8)
{
    uint8_t mostbit = *r8 & 0x80;
    *r8 <<= 1;

    setflag(regs, FLAG_C, (mostbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}


void sra_r8(regptr regs, uint8_t* r8)
{
    uint8_t mostbit = *r8 & 0x80;
    uint8_t leastbit = *r8 & 0x1;
    *r8 = (*r8 >> 1) | mostbit;

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

void srl_r8(regptr regs, uint8_t* r8)
{
    uint8_t leastbit = *r8 & 0x1;
    *r8 >>=1;

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, (*r8 == 0));
}

execute_cb_instruction(regptr regs, uint8_t* memory, uint8_t opcode)
{
    uint8_t* r8 = r8_adr(regs, memory, opcode&0x7);
    uint8_t bit = (opcode >> 3) & 7;

    switch (opcode >>  6)
    {
    case 0x0: 
    {
        switch (opcode >> 3)
        {
        case 0x0:rlc_r8(regs, r8); break;
        case 0x1:rrc_r8(regs, r8); break;
        case 0x2:rl_r8(regs, r8); break;
        case 0x3:rr_r8(regs, r8); break;
        case 0x4:sla_r8(regs, r8); break;
        case 0x5:sra_r8(regs, r8); break;
        case 0x6:swap_r8(regs, r8); break;
        case 0x7:srl_r8(regs, r8); break;
        default:
            break;
        } 
    }
    case 0x1:bit_b3_r8(regs, r8, bit); break;
    case 0x2:res_b3_r8(regs, r8, bit); break;
    case 0x3:set_b3_r8(regs, r8, bit); break;
    default:

        break;
    }
}