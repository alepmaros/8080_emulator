#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void unimplementedInstruction(State8080* state)
{
    // Add more error information here
    printf("Error, unimplemented instruction\n");
    exit(1);
}

// Need to double check this
int parity(uint8_t num)
{
    int bits = 0;
    int i;

    for (i = 0; i < 8; i++)
    {
        bits += ((num >> i) & 0x1);
    }

    return 0 == (bits & 0x1);
}


void print_state(State8080* state)
{
    printf( "------STATE8080------\n"
            " A: %02x\n"
            " B: %02x\n"
            " C: %02x\n"
            " D: %02x\n"
            " E: %02x\n"
            " H: %02x\n"
            " L: %02x\n"
            "SP: %04x\n"
            "PC: %04x\n"
            "--------FLAGS--------\n"
            " Z: %d\n"
            " S: %d\n"
            " P: %d\n"
            "CY: %d\n"
            "AC: %d\n"
            "---------------------\n"
            "CYCLES: %llu\n"
            "N_INSTRUCTIONS: %llu\n"
            "---------ENDD--------\n",
            state->a, state->b, state->c, state->d, state->e, state->h, 
            state->l, state->sp, state->pc, state->flags.z, state->flags.s,
            state->flags.p, state->flags.cy, state->flags.ac, state->cycles,
            state->n_instructions);
}