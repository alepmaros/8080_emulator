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
            state->cycles += 3;
            break;
        case 0x87: 
            answer += (uint16_t) state->a; break;
    }

    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);
}

void inst_adc(State8080* state)
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
            state->cycles += 3;
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

void inst_adi(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);
    
    state->cycles += 3;
    state->pc += 1;
}

void inst_aci(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
    state->flags.z = ((answer & 0xff) == 0);
    state->flags.s = ((answer & 0x80) != 0);
    state->flags.cy = (answer > 0xff);
    state->flags.p = parity(answer & 0xff);
    state->a = (answer & 0xff);

    state->cycles += 3;
    state->pc += 1;
}