/*
 *
 * A few notes:
 *  AC (Auxillary carry) is not implemented since Space Invaders does not use it.
 *
 */

#include "emulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "instructions_arithmetic.h"
#include "instructions_branch.h"
#include "instructions_data_transfer.h"
#include "instructions_logical.h"
#include "instructions_stack_io_machine.h"

void emulate8080(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        // NOP
        case 0x00:
            break;

        // LXI B,word
        case 0x01:
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;

        /**/

        // MOV B,C
        case 0x41:
            state->b = state->c;
            break;

        // MOV B,D
        case 0x42:
            state->b = state->d;
            break;

        // MOV B,E
        case 0x43:
            state->b = state->e;
            break;

        /**/

        // ADD R
        case 0x80: 
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x86:
        case 0x87:
            inst_add(state);

        // ADI D8
        case 0xc6:
            inst_adi(state);

        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8e:
        case 0x8f:
            inst_adc(state);

    }

    state->pc += 1;
}