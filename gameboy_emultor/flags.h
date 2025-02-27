#include "registers.h"

#define FLAG_Z_BIT  7   /* Zero flag */
#define FLAG_N_BIT  6   /* Subtraction flag (BCD) */
#define FLAG_H_BIT  5   /* Half Carry flag (BCD) */
#define FLAG_C_BIT  4   /* Carry flag */

/* Define flag bit masks */
#define FLAG_Z  (1 << FLAG_Z_BIT)   /* 0x80 */
#define FLAG_N  (1 << FLAG_N_BIT)   /* 0x40 */
#define FLAG_H  (1 << FLAG_H_BIT)   /* 0x20 */
#define FLAG_C  (1 << FLAG_C_BIT)   /* 0x10 */

void setflag(regptr registers, uint8_t flag, int value);
int getFlag(regptr registers, uint8_t flag);
void setzeroflag(regptr registers);
void rlca(regptr regs);
void rrca(regptr regs);
void rla(regptr regs);
void rra(regptr regs);
void cpl(regptr regs);
void scf(regptr regs);
void ccf(regptr regs);
void daa(regptr regs);
