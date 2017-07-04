#include "instructions_data_transfer.h"

void inst_lxi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    state->sp = (opcode[2] << 8) | opcode[1];
    state->pc += 2;
    state->cycles += 6;
}