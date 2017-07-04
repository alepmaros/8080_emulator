#include "instructions_data_transfer.h"

void inst_lxi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x31:
            state->sp = (opcode[2] << 8) | opcode[1]; break;

    }
    
    state->pc += 3;
    state->cycles += 10;
}