#include "registers.h"
#include "flags.h"

void registers_init(regptr registers) {
    registers->AF = 0;
    registers->BC = 0;
    registers->DE = 0;
    registers->HL = 0;
    registers->SP = 0;
    registers->PC = 0;
}

/* Function to get address of 8-bit registers */
uint8_t* r8_adr(regptr registers, uint8_t* memory, int index) {
    static uint8_t* r8_adress[8]; /* Declare array first */

    /* Initialize array elements */
    r8_adress[0] = &(registers->B);
    r8_adress[1] = &(registers->C);
    r8_adress[2] = &(registers->D);
    r8_adress[3] = &(registers->E);
    r8_adress[4] = &(registers->H);
    r8_adress[5] = &(registers->L);
    r8_adress[6] = (memory + registers->HL); /* Memory at HL */
    r8_adress[7] = &(registers->A);

    return r8_adress[index];
}

/* Function to get address of 16-bit registers */
uint16_t* r16_adr(regptr registers, int index) {
    static uint16_t* r16_adress[4]; /* Declare array first */

    /* Initialize array elements */
    r16_adress[0] = &(registers->BC);
    r16_adress[1] = &(registers->DE);
    r16_adress[2] = &(registers->HL);
    r16_adress[3] = &(registers->SP);

    return r16_adress[index];
}

/* Function to get address of 16-bit registers for stack operations */
uint16_t* r16_stk(regptr registers, int index) {
    static uint16_t* r16_adress[4]; /* Declare array first */

    /* Initialize array elements */
    r16_adress[0] = &(registers->BC);
    r16_adress[1] = &(registers->DE);
    r16_adress[2] = &(registers->HL);
    r16_adress[3] = &(registers->AF);

    return r16_adress[index];
}