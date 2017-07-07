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

void inst_xchg(State8080* state)
{
    //unsigned char *opcode = &state->memory[state->pc];
    uint8_t temp = 0;

    temp        = state->h;
    state->h    = state->d;
    state->d    = temp;

    temp        = state->l;
    state->l    = state->e;
    state->e    = temp;

    state->cycles   += 4;
    state->pc       += 1;
}

void inst_mov(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x40:
            state->b = state->b;
            break;
        case 0x41:
            state->b = state->c;
            break;
        case 0x42:
            state->b = state->d;
            break;
        case 0x43:
            state->b = state->e;
            break;
        case 0x44:
            state->b = state->h;
            break;
        case 0x45:
            state->b = state->l;
            break;
        case 0x46:
            state->b = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x47:
            state->b = state->a;
            break;
        case 0x48:
            state->c = state->b;
            break;
        case 0x49:
            state->c = state->c;
            break;
        case 0x4a:
            state->c = state->d;
            break;
        case 0x4b:
            state->c = state->e;
            break;
        case 0x4c:
            state->c = state->h;
            break;
        case 0x4d:
            state->c = state->l;
            break;
        case 0x4e:
            state->c = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x4f:
            state->c = state->a;
            break;
        case 0x50:
            state->d = state->b;
            break;
        case 0x51:
            state->d = state->c;
            break;
        case 0x52:
            state->d = state->d;
            break;
        case 0x53:
            state->d = state->e;
            break;
        case 0x54:
            state->d = state->h;
            break;
        case 0x55:
            state->d = state->l;
            break;
        case 0x56:
            state->d = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x57:
            state->d = state->a;
            break;
        case 0x58:
            state->e = state->b;
            break;
        case 0x59:
            state->e = state->c;
            break;
        case 0x5a:
            state->e = state->d;
            break;
        case 0x5b:
            state->e = state->e;
            break;
        case 0x5c:
            state->e = state->h;
            break;
        case 0x5d:
            state->e = state->l;
            break;
        case 0x5e:
            state->e = state->memory[ (state->h << 8) | state-> l ];
            state->cycles += 2;
            break;
        case 0x5f:
            state->e = state->a;
            break;
        case 0x60:
            state->h = state->b;
            break;
        case 0x61:
            state->h = state->c;
            break;
        case 0x62:
            state->h = state->d;
            break;
        case 0x63:
            state->h = state->e;
            break;
        case 0x64:
            state->h = state->h;
            break;
        case 0x65:
            state->h = state->l;
            break;
        case 0x66:
            state->h = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x67:
            state->h = state->a;
            break;
        case 0x68:
            state->l = state->b;
            break;
        case 0x69:
            state->l = state->c;
            break;
        case 0x6a:
            state->l = state->d;
            break;
        case 0x6b:
            state->l = state->e;
            break;
        case 0x6c:
            state->l = state->h;
            break;
        case 0x6d:
            state->l = state->l;
            break;
        case 0x6e:
            state->l = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x6f:
            state->l = state->a;
            break;
        case 0x70:
            state->memory[ (state->h << 8) | state->l ] = state->b;
            state->cycles += 2;
            break;
        case 0x71:
            state->memory[ (state->h << 8) | state->l ] = state->c;
            state->cycles += 2;
            break;
        case 0x72:
            state->memory[ (state->h << 8) | state->l ] = state->d;
            state->cycles += 2;
            break;
        case 0x73:
            state->memory[ (state->h << 8) | state->l ] = state->e;
            state->cycles += 2;
            break;
        case 0x74:
            state->memory[ (state->h << 8) | state->l ] = state->h;
            state->cycles += 2;
            break;
        case 0x75:
            state->memory[ (state->h << 8) | state->l ] = state->l;
            state->cycles += 2;
            break;
        case 0x77:
            state->memory[ (state->h << 8) | state->l ] = state->a;
            state->cycles += 2;
            break;
        case 0x78:
            state->a = state->b;
            break;
        case 0x79:
            state->a = state->c;
            break;
        case 0x7a:
            state->a = state->d;
            break;
        case 0x7b:
            state->a = state->e;
            break;
        case 0x7c:
            state->a = state->h;
            break;
        case 0x7d:
            state->a = state->l;
            break;
        case 0x7e:
            state->a = state->memory[ (state->h << 8) | state->l ];
            state->cycles += 2;
            break;
        case 0x7f:
            state->a = state->a;
            break;
    }

    state->cycles += 5;
    state->pc += 1;
}