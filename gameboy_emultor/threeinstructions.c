#include "threeinstructions.h"

void add_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint16_t result = regs->A + value;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF)) > 0xF);
	setflag(regs, FLAG_C, result > 0xFF);

	regs->A = (uint8_t)result;
}

void adc_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A + value + carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, ((regs->A & 0xF) + (value & 0xF) + carry) > 0xF);
	setflag(regs, FLAG_C, result > 0xFF);

	regs->A = (uint8_t)result;
}

void sub_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint16_t result = regs->A - value;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, (regs->A & 0xF) < (value & 0xF));
	setflag(regs, FLAG_C, regs->A < value);

	regs->A = (uint8_t)result;
}

void sbc_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t carry = getFlag(regs, FLAG_C);
	uint16_t result = regs->A - value - carry;

	setflag(regs, FLAG_Z, (result & 0xFF) == 0);
	setflag(regs, FLAG_N, 1);
	setflag(regs, FLAG_H, ((regs->A & 0xF) < ((value & 0xF) + carry)));
	setflag(regs, FLAG_C, regs->A < (value + carry));

	regs->A = (uint8_t)result;
}

void and_a_imm8(regptr regs, uint8_t* memory)
{
    uint8_t value = memory[++regs->PC];
    uint16_t result = regs->A & value;

    setflag(regs, FLAG_Z, (result & 0xFF) == 0);
    setflag(regs, FLAG_N, 0);
    setflag(regs, FLAG_H, ((regs->A & 0xF) < (value & 0xF)));
    setflag(regs, FLAG_C, 0);

    regs->A = (uint8_t)result;
}

void xor_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	regs->A ^= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void or_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	regs->A |= value;

	setflag(regs, FLAG_Z, regs->A == 0);
	setflag(regs, FLAG_N, 0);
	setflag(regs, FLAG_H, 0);
	setflag(regs, FLAG_C, 0);
}

void cp_a_imm8(regptr regs, uint8_t* memory)
{
	uint8_t value = memory[++regs->PC];
	uint8_t result = regs->A - value;

	setflag(regs, FLAG_Z, result == 0);          // Zero flag: Set if A == value
	setflag(regs, FLAG_N, 1);                    // Subtraction flag: Always set
	setflag(regs, FLAG_H, ((regs->A & 0xF) - (value & 0xF)) < 0); // Half-carry flag
	setflag(regs, FLAG_C, regs->A < value);      // Carry flag: Set if borrow occurs
}

void group_33_instructions(regptr regs, uint8_t* memory, uint8_t opcode)
{
    switch (opcode)
    {
        // Ret Instructions (with conditions)
    case 0xC0: ret_nz(regs, memory); break; // RET NZ
    case 0xC8: ret_z(regs, memory); break;  // RET Z
    case 0xD0: ret_nc(regs, memory); break; // RET NC
    case 0xD8: ret_c(regs, memory); break;  // RET C

    // Ret (without condition) and Reti
    case 0xC1: ret(regs, memory); break;    // RET
    case 0xD1: reti(regs, memory); break;   // RETI

    // Jump Instructions (with conditions)
    case 0xE9: jp_hl(regs, memory); break;  // JP HL
    case 0xC2: jp_nz(regs, memory); break;  // JP NZ, imm16
    case 0xCA: jp_z(regs, memory); break;   // JP Z, imm16
    case 0xD2: jp_nc(regs, memory); break;  // JP NC, imm16
    case 0xDA: jp_c(regs, memory); break;   // JP C, imm16
    case 0xC3: jp_imm16(regs, memory); break; // JP imm16

    // Call Instructions (with conditions)
    case 0xE4: call_nz(regs, memory); break; // CALL NZ, imm16
    case 0xEC: call_z(regs, memory); break;  // CALL Z, imm16
    case 0xD4: call_nc(regs, memory); break; // CALL NC, imm16
    case 0xDC: call_c(regs, memory); break;  // CALL C, imm16
    case 0xCD: call_imm16(regs, memory); break; // CALL imm16

    // RST instructions (specific targets)
    case 0xFF: rst_tgt3(regs, memory); break; // RST 38h
    case 0xF7: rst_tgt2(regs, memory); break; // RST 30h
    case 0xEF: rst_tgt1(regs, memory); break; // RST 20h
    case 0xE7: rst_tgt0(regs, memory); break; // RST 10h

    // Pop and Push instructions for 16-bit registers
    case 0xF1: pop_r16stk(regs, memory, opcode); break; // POP AF
    case 0xF5: push_r16stk(regs, memory, opcode); break; // PUSH AF

    // Other instructions (such as arithmetic and logic)
    case 0x06: add_a_imm8(regs, memory); break;     // ADD A, imm8
    case 0x0E: adc_a_imm8(regs, memory); break;     // ADC A, imm8
    case 0x16: sub_a_imm8(regs, memory); break;     // SUB A, imm8
    case 0x1E: sbc_a_imm8(regs, memory); break;     // SBC A, imm8
    case 0x26: and_a_imm8(regs, memory); break;     // AND A, imm8
    case 0x2E: xor_a_imm8(regs, memory); break;     // XOR A, imm8
    case 0x36: or_a_imm8(regs, memory); break;      // OR A, imm8
    case 0x3E: cp_a_imm8(regs, memory); break;      // CP A, imm8

    // LD Instructions (16-bit immediate data and registers)
    case 0x20: ldh_imm8_a(regs, memory); break;     // LDH (imm8), A
    case 0x22: ldh_a_c(regs, memory); break;        // LD (C), A
    case 0x28: add_sp_imm8(regs, memory); break;    // ADD SP, imm8
    case 0x2A: ld_imm16_a(regs, memory); break;     // LD (imm16), A
    case 0x30: ldh_a_imm8(regs, memory); break;     // LDH A, (imm8)
    case 0x32: ldh_a_c(regs, memory); break;        // LD (C), A
    case 0x38: ld_hl_sp_imm8(regs, memory); break;  // LD HL, SP + imm8
    case 0x39: ld_sp_hl(regs, memory); break;       // LD SP, HL
    case 0x3A: ld_a_imm16(regs, memory); break;     // LD A, (imm16)

    // Enable/Disable Interrupts
    case 0x33: di(regs); break;                    // DI (disable interrupts)
    case 0x3B: ei(regs); break;                    // EI (enable interrupts)
    default:
        break;
    }
}
