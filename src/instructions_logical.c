#include "instructions_logical.h"

#include "utils.h"

void inst_cpi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    
    uint8_t answer = (uint8_t) state->a;
    answer        -= opcode[1];

    state->flags.z  = (answer == 0);
    state->flags.s  = ((answer & 0x80) != 0);
    state->flags.cy = state->a < opcode[1];
    state->flags.p  = parity(answer & 0xff);
    
    state->cycles   += 7;
    state->pc       += 2;
}