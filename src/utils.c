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