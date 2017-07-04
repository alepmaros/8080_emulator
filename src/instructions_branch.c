#include "instructions_branch.h"

void inst_jmp(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    state->pc = (opcode[2] << 8) | opcode[1];
    state->cycles += 10;
}

void inst_call(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t next_inst = state->pc += 3;
    state->memory[state->sp - 1] = (uint8_t) (next_inst >> 8);
    state->memory[state->sp - 2] = (uint8_t) next_inst;
    state->sp -= 2;
    state->pc = (opcode[2] << 8) | opcode[1];

    state->cycles += 17;
}