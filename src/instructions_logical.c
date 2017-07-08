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

void inst_rrc(State8080* state)
{
    uint8_t temp = state->a;
    
    state->a        = (temp >> 1) | ((temp & 0x01) << 7);
    state->flags.cy = temp & 0x01;

    state->cycles   += 4;
    state->pc       += 1;
}

void inst_ani(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    state->a = state->a & opcode[1];

    state->flags.z  = state->a == 0;
    state->flags.s  = ((state->a & 0x80) != 0);
    state->flags.p  = parity(state->a);
    state->flags.cy = 0;
    state->flags.ac = 0;

    state->cycles   += 7;
    state->pc       += 2;
}

void inst_ana(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0xa0:
            state->a = state->a & state->b;
            break;
        case 0xa1:
            state->a = state->a & state->c;
            break;
        case 0xa2:
            state->a = state->a & state->d;
            break;
        case 0xa3:
            state->a = state->a & state->e;
            break;
        case 0xa4:
            state->a = state->a & state->h;
            break;
        case 0xa5:
            state->a = state->a & state->l;
            break;
        case 0xa6: // ANA M
            state->a = state->a & state->memory[ (state->h << 8) | state->l ];
            state->cycles += 3;
            break;
        case 0xa7:
            state->a = state->a & state->a;
            break;
    }

    state->flags.z  = state->a == 0;
    state->flags.s  = ((state->a & 0x80) != 0);
    state->flags.p  = parity(state->a);
    state->flags.cy = 0;

    state->cycles   += 4;
    state->pc       += 1;
}

void inst_xra(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0xa8:
            state->a = state->a ^ state->b;
            break;
        case 0xa9:
            state->a = state->a ^ state->c;
            break;
        case 0xaa:
            state->a = state->a ^ state->d;
            break;
        case 0xab:
            state->a = state->a ^ state->e;
            break;
        case 0xac:
            state->a = state->a ^ state->h;
            break;
        case 0xad:
            state->a = state->a ^ state->l;
            break;
        case 0xae: // XRA M
            state->a = state->a ^ state->memory[ (state->h << 8) | state->l ];
            state->cycles+= 3;
            break;
        case 0xaf:
            state->a = state->a ^ state->a;
            break;
    }

    state->flags.z  = state->a == 0;
    state->flags.s  = ((state->a & 0x80) != 0);
    state->flags.p  = parity(state->a);
    state->flags.cy = 0;
    state->flags.ac = 0;

    state->cycles   += 4;
    state->pc       += 1;
}