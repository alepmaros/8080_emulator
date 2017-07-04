#include "instructions_data_transfer.h"

#ifdef __debug
#include <stdio.h>
#endif

void inst_lxi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x01:
            state->b = opcode[2];
            state->c = opcode[1];
            break;
        case 0x11:
            state->d = opcode[2];
            state->e = opcode[1];
            break;
        case 0x21:
            state->h = opcode[2];
            state->l = opcode[1];
            break;
        case 0x31:
            state->sp = (opcode[2] << 8) | opcode[1];
            break;

    }
    
    state->pc += 3;
    state->cycles += 10;
}

void inst_mvi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x06:
            state->b = opcode[1];
            break;
        case 0x0e:
            state->c = opcode[1];
            break;
        case 0x16:
            state->d = opcode[1];
            break;
        case 0x1e:
            state->e = opcode[1];
            break;
        case 0x26:
            state->h = opcode[1];
            break;
        case 0x2e:
            state->l = opcode[1];
            break;
        case 0x36:
            state->memory[(state->h<<8) | (state->l)] = opcode[1];
            state->cycles += 3;
            break;
        case 0x3e:
            state->a = opcode[1];
            break;
    }

    state->pc += 2;
    state->cycles += 7;
}

void inst_ldax(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x0a:
            state->a = state->memory[ (state->b << 8) | state->c ];
            break;
        case 0x1a:
            state->a = state->memory[ (state->d << 8) | state->e ];
            break;
    }

    state->pc += 1;
    state->cycles += 7;
}