#pragma once
#include <stdint.h>  /* Use C-style header instead of cstdint */

/* C-style struct definition */
typedef struct registers {
    union {
        struct {
            uint8_t F;  /* Flags (low byte) */
            uint8_t A;  /* Accumulator (high byte) */
        };
        uint16_t AF;    /* Combined 16-bit register */
    };
    union {
        struct {
            uint8_t C;  /* Low byte */
            uint8_t B;  /* High byte */
        };
        uint16_t BC;    /* Combined 16-bit register */
    };
    union {
        struct {
            uint8_t E;  /* Low byte */
            uint8_t D;  /* High byte */
        };
        uint16_t DE;    /* Combined 16-bit register */
    };
    union {
        struct {
            uint8_t L;  /* Low byte */
            uint8_t H;  /* High byte */
        };
        uint16_t HL;    /* Combined 16-bit register */
    };
    uint16_t SP;        /* Stack Pointer */
    uint16_t PC;        /* Program Counter/Pointer */
    uint8_t IME; // enables intterps
    uint8_t IME_enable_delay;  // Delay flag for EI instruction 
}registers, * regptr;

void registers_init(regptr registers);
uint8_t* r8_adr(regptr registers, uint8_t* memory, int index);
uint16_t* r16_adr(regptr registers, int index);
uint16_t* r16_stk(regptr registers, int index);
