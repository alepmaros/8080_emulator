#include "emulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "disassemble.h"
#include "instructions_arithmetic.h"
#include "instructions_branch.h"
#include "instructions_data_transfer.h"
#include "instructions_logical.h"
#include "instructions_stack_io_machine.h"

State8080* initializeState8080()
{
    State8080* state = calloc(1, sizeof(State8080));
    // 64K of RAM
    state->memory = calloc(1, 64 * 1024);
    return state;
}

void loadRomToMemory(char* fname, State8080* state)
{
    FILE *f = fopen(fname, "rb");
    if (f == NULL)
    {
        printf("Error: Could not open %s\n", fname);
        exit(1);
    }

    // Get the file size and read it into a memory buffer
    fseek(f, 0L, SEEK_END);
    long int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    if (fsize > 64*1024)
    {
        printf("Error: ROM to big for memory %li", fsize);
        exit(2);
    }

    fread(state->memory, fsize, 1, f);
    fclose(f);
}

void emulate8080(State8080* state)
{
#ifdef __debug
    print_state(state);
    disassemble8080(state);
    printf("\n");
#endif

    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        // NOP
        case 0x00:
            state->pc += 1;
            state->cycles += 4;
            break;

        // LXI
        case 0x01:
        case 0x11:
        case 0x21:
        case 0x31:
            inst_lxi(state);
            break;

        // LDAX
        case 0x0a:
        case 0x1a:
            inst_ldax(state);
            break;

        // MVI
        case 0x06:
        case 0x0e:
        case 0x16:
        case 0x1e:
        case 0x26:
        case 0x2e:
        case 0x36:
        case 0x3e:
            inst_mvi(state);
            break;

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
            break;

        // ADI D8
        case 0xc6:
            inst_adi(state);
            break;

        // ADC
        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8e:
        case 0x8f:
            inst_adc(state);
            break;

        case 0xc3:
            inst_jmp(state);
            break;

        case 0xcd:
            inst_call(state);
            break;

        default:
            // Since unimplementedInstructions ends the program
            print_state(state);
            disassemble8080(state);
            unimplementedInstruction(state);
            break;
    }

#ifdef __debug
    if (state->n_instructions > 10)
        getchar();
#endif

    state->n_instructions++;
}