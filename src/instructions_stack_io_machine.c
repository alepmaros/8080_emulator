#include "instructions_stack_io_machine.h"

void inst_push(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0xc5: // PUSH B
            state->memory[state->sp-1] = state->b;
            state->memory[state->sp-2] = state->c;
            break;
        case 0xd5: // PUSH D
            state->memory[state->sp-1] = state->d;
            state->memory[state->sp-2] = state->e;
            break;
        case 0xe5: // PUSH H
            state->memory[state->sp-1] = state->h;
            state->memory[state->sp-2] = state->l;
            break;
        case 0xf5: // PUSH PSW
            state->memory[state->sp-1] = state->a;
            state->memory[state->sp-2] = (state->flags.cy << 0) |
                                         (state->flags.p  << 2) |
                                         (state->flags.ac << 4) |
                                         (state->flags.z  << 6) |
                                         (state->flags.s  << 7) |
                                         0x02;                 
            break;
    }

    state->sp       -= 2;
    state->pc       += 1;
    state->cycles   += 11;
}

void inst_pop(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0xc1: // POP B
            state->c = state->memory[state->sp];
            state->b = state->memory[state->sp+1];
            break;
        case 0xd1: // POP D
            state->e = state->memory[state->sp];
            state->d = state->memory[state->sp+1];
            break;
        case 0xe1: // POP H
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp+1];
            break;
        case 0xf1: // POP PSW
        {
            uint8_t psw = state->memory[state->sp];
            state->flags.cy = (psw & 0x01 ? 1 : 0 );
            state->flags.p  = (psw & 0x04 ? 1 : 0 );
            state->flags.ac = (psw & 0x10 ? 1 : 0 ); 
            state->flags.z  = (psw & 0x40 ? 1 : 0 );
            state->flags.s  = (psw & 0x80 ? 1 : 0 );
            state->a = state->memory[state->sp+1];
            break;
        }
    }

    state->sp       += 2;
    state->pc       += 1;
    state->cycles   += 10;
}