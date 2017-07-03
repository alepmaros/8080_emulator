/*
 *
 * A few notes:
 *  AC (Auxillary carry) is not implemented since Space Invaders does not use it.
 *
 */

#include "emulator.h"

#include <stdio.h>
#include <stdlib.h>

void unimplementedInstruction(State8080* state)
{
    // Add more error information here
    printf("Error, unimplemented instruction\n",)l
    exit(1);
}

// Need to double check this
int parity(uint8_t num)
{
    int bits = 0;
    int i;

    for (i; i < 8; i++)
    {
        bits += ((num >> i) & 0x1);
    }

    return 0 == (bits & 0x1);
}

// add
// ADD R 4 cycles
// ADD M 7 cycles
void emu_add(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = (uint16_t) state->a;

    switch(*opcode)
        case 0x80:
            answer += (uint16_t) state->b; break;
        case 0x81:
            answer += (uint16_t) state->c; break;
        case 0x82:
            answer += (uint16_t) state->d; break;
        case 0x83:
            answer += (uint16_t) state->e; break;
        case 0x84:
            answer += (uint16_t) state->h; break;
        case 0x85:
            answer += (uint16_t) state->l; break;
        case 0x86:
            answer += (uint16_t) state->memory[(state->h<<8) | (state->l)];
            break;
        case 0x87: 
            answer += (uint16_t) state->a; break;

    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);
}

// adi
// ADI 7 cycles
void emu_adi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);
}

void emu_adc(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = (uint16_t) state->a + state->flags.cy;

    switch(*opcode)
    {
        case 0x88:
            answer += (uint16_t) state->b; break;
        case 0x89:
            answer += (uint16_t) state->c; break;
        case 0x8a:
            answer += (uint16_t) state->d; break;
        case 0x8b:
            answer += (uint16_t) state->e; break;
        case 0x8c:
            answer += (uint16_t) state->h; break;
        case 0x8d:
            answer += (uint16_t) state->l; break;
        case 0x8e:
            answer += (uint16_t) state->memory[(state->h<<8) | (state->l)];
            break;
        case 0x8f:
            answer += (uint16_t) state->a; break;
    }

    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);
}

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
            emu_add(state);

        // ADI D8
        case 0xc6:
            emu_adi(state);

        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8e:
        case 0x8f:
            emu_adc(state);

    }

    state->pc += 1;
}