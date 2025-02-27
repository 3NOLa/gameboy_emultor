#include "flags.h"

/* Set a specific flag */
void setflag(regptr registers, uint8_t flag, int value) {
    if (value) {
        registers->F |= flag;
    }
    else {
        registers->F &= ~flag;
    }
}

/* Get the state of a flag */
int getFlag(regptr registers, uint8_t flag) {
    return (registers->F & flag) != 0;
}

/* Set the zero flag based on result */
void setzeroflag(regptr registers) {
    setflag(registers, FLAG_Z, 1);
}

void rlca(regptr regs) {
    uint8_t mostbit = regs->A & 0x80;

    setflag(regs, FLAG_C, (mostbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, 0);

    regs->A = (regs->A << 1) | (mostbit >> 7);
}

void rrca(regptr regs) {
    uint8_t leastbit = regs->A & 0x1;

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, 0);

    regs->A = (regs->A >> 1) | (leastbit << 7);
}

void rla(regptr regs) {
    uint8_t mostbit = regs->A & 0x80;

    regs->A = ((regs->A << 1) | getFlag(regs, FLAG_C));

    setflag(regs, FLAG_C, (mostbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, 0);
}

void rra(regptr regs) {
    uint8_t leastbit = regs->A & 0x1;

    regs->A = ((regs->A >> 1) | (getFlag(regs, FLAG_C) << 7));

    setflag(regs, FLAG_C, (leastbit != 0));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
    setflag(regs, FLAG_Z, 0);
}

void cpl(regptr regs)
{
    regs->A = ~regs->A;

    setflag(regs, FLAG_N, 1);
    setflag(regs, FLAG_H, 1);
}

void scf(regptr regs)
{
    setflag(regs, FLAG_C, 1);
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
}

void ccf(regptr regs)
{
    setflag(regs, FLAG_C, ~getFlag(regs, FLAG_C));
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, 0);
}


void daa(regptr regs) {
    uint8_t correction = 0;
    uint8_t A = regs->A;

    // Check if we need correction based on flags
    if ((A & 0x0F) > 9 || getFlag(regs, FLAG_H)) {
        correction |= 0x06;
    }
    if ((A > 0x99) || getFlag(regs, FLAG_C)) {
        correction |= 0x60;
        setflag(regs, FLAG_C, 1); // Set carry flag
    }

    regs->A += correction;
    setflag(regs, FLAG_H, 0); // H flag is always cleared
    setflag(regs, FLAG_Z, regs->A == 0);

}