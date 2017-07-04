#include "instructions_branch.h"

void inst_jmp(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    state->pc = (opcode[2] << 8) | opcode[1];
    state->cycles += 6;
}