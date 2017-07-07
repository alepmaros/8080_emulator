#include "instructions_branch.h"

void inst_jmp(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];
    switch(*opcode)
    {
        case 0xc2: // JNZ
            if (!state->flags.z)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xc3: // JMP
            state->pc = (opcode[2] << 8) | opcode[1];
            break;
        case 0xca: // JZ
            if (state->flags.z)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xd2: // JNC
            if(!state->flags.cy)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xda: // JC
            if (state->flags.cy)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xf2: // JP
            if (!state->flags.s)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xfa: // JM
            if (state->flags.s)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xea: // JPE
            if (state->flags.p)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
        case 0xe2: // JPO
            if (!state->flags.p)
            {
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else
            {
                state->pc += 3;
            }
            break;
    }

    
    state->cycles += 10;
}

void inst_call(State8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    uint16_t next_inst = state->pc += 3;
    state->memory[state->sp - 1] = (uint8_t) (next_inst >> 8);
    state->memory[state->sp - 2] = (uint8_t) next_inst;
    state->sp -= 2;
    state->pc = (opcode[2] << 8) | opcode[1];

    state->cycles += 17;
}

void inst_ret(State8080* state)
{
    //unsigned char *opcode = &state->memory[state->pc];

    state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
    state->sp       += 2;
    state->cycles   += 10;
}