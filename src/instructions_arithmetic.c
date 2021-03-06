/*
 *
 * A few notes:
 *  AC (Auxillary carry) is not implemented since Space Invaders does not use it.
 *
 */

#include "instructions_arithmetic.h"
#include "utils.h"

#include <stdint.h>

// add
// ADD R 4 cycles
// ADD M 7 cycles
void inst_add(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t answer = (uint16_t) state->a;

    switch(*opcode)
    {
        case 0x80:
            answer += (uint16_t) state->b;
            break;
        case 0x81:
            answer += (uint16_t) state->c;
            break;
        case 0x82:
            answer += (uint16_t) state->d;
            break;
        case 0x83:
            answer += (uint16_t) state->e;
            break;
        case 0x84:
            answer += (uint16_t) state->h;
            break;
        case 0x85:
            answer += (uint16_t) state->l;
            break;
        case 0x86:
            answer += (uint16_t) state->memory[(state->h<<8) | (state->l)];
            state->cycles += 3;
            break;
        case 0x87: 
            answer += (uint16_t) state->a;
            break;
    }

    state->flags.z  = ((answer & 0xff) == 0);
    state->flags.s  = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p  = parity(answer & 0xff);
    state->a        = (answer & 0xff);

    state->cycles   += 4;
    state->pc       += 1;
}

void inst_adc(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t answer = (uint16_t) state->a + state->flags.cy;

    switch(*opcode)
    {
        case 0x88:
            answer += (uint16_t) state->b;
            break;
        case 0x89:
            answer += (uint16_t) state->c;
            break;
        case 0x8a:
            answer += (uint16_t) state->d;
            break;
        case 0x8b:
            answer += (uint16_t) state->e;
            break;
        case 0x8c:
            answer += (uint16_t) state->h;
            break;
        case 0x8d:
            answer += (uint16_t) state->l;
            break;
        case 0x8e:
            answer += (uint16_t) state->memory[(state->h<<8) | (state->l)];
            state->cycles += 3;
            break;
        case 0x8f:
            answer += (uint16_t) state->a;
            break;
    }

    state->flags.z  = ((answer & 0xff) == 0);
    state->flags.s  = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p  = parity(answer & 0xff);
    state->a        = (answer & 0xff);

    state->cycles   += 4;
    state->pc       += 1;
}

void inst_adi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];

    state->flags.z  = ((answer & 0xff) == 0);
    state->flags.s  = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p  = parity(answer & 0xff);
    state->a        = (answer & 0xff);
    
    state->cycles   += 7;
    state->pc       += 2;
}

void inst_aci(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];

    state->flags.z  = ((answer & 0xff) == 0);
    state->flags.s  = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p  = parity(answer & 0xff);
    state->a        = (answer & 0xff);

    state->cycles   += 7;
    state->pc       += 2;
}

void inst_inx(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x03:
            state->c++;
            if (state->c == 0)
                state->b++;
            break;
        case 0x13:
            state->e++;
            if (state->e == 0)
                state->d++;
            break;
        case 0x23:
            state->l++;
            if (state->l == 0)
                state->h++;
            break;
        case 0x33:
            state->sp++;
            break;
    }

    state->cycles   += 5;
    state->pc       += 1;
}

void inst_dcr(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t answer = 0;

    switch(*opcode)
    {
        case 0x05:
            answer = state->b - 1;
            state->b = answer & 0xff;
            break;
        case 0x0d:
            answer = state->c - 1;
            state->c = answer & 0xff;
            break;
        case 0x15:
            answer = state->d - 1;
            state->d = answer & 0xff;
            break;
        case 0x1d:
            answer = state->e - 1;
            state->e = answer & 0xff;
            break;
        case 0x25:
            answer = state->h - 1;
            state->h = answer & 0xff;
            break;
        case 0x2d:
            answer = state->l - 1;
            state->l = answer & 0xff;
            break;
        case 0x35:
        {
            uint16_t addr = (state->h << 8) | state->l;
            answer = state->memory[addr] - 1;
            state->memory[addr] = answer & 0xff;
            state->cycles += 5;
        }
        case 0x3d:
            answer = state->a - 1;
            state->a = answer;
    }

    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.p = parity(answer & 0xff);

    state->cycles   += 5;
    state->pc       += 1;
}

void inst_dad(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint32_t hl     = (state->h << 8) | state->l;
    uint32_t rl     = 0;
    uint32_t answer = 0;

    switch(*opcode)
    {
        case 0x09: // DAD B
            rl = (state->b << 8) | state->c;
            break;
        case 0x19: // DAD D
            rl = (state->d << 8) | state->e;
            break;
        case 0x29: // DAD H
            rl = (state->h << 8) | state->l;
            break;
        case 0x39: // DAD SP
            rl = state->sp;
            break;
    }

    answer = hl + rl;

    state->h        = (answer >> 8) & 0xff;
    state->l        = (answer >> 0) & 0xff;
    state->flags.cy = (answer & 0xffff0000) > 0;

    state->pc       += 1;
    state->cycles   += 10;
}