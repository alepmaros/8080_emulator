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

        // INX
        case 0x03:
        case 0x13:
        case 0x23:
        case 0x33:
            inst_inx(state);
            break;

        // DCR
        case 0x05:
        case 0x0d:
        case 0x15:
        case 0x1d:
        case 0x25:
        case 0x2d:
        case 0x35:
        case 0x3d:
            inst_dcr(state);
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

        // Change this to if later?
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4e:
        case 0x4f:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5a:
        case 0x5b:
        case 0x5c:
        case 0x5d:
        case 0x5e:
        case 0x5f:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0x6e:
        case 0x6f:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7a:
        case 0x7b:
        case 0x7c:
        case 0x7d:
        case 0x7e:
        case 0x7f:
            inst_mov(state);
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

        case 0xc2:
        case 0xc3:
        case 0xca:
        case 0xd2:
        case 0xda:
        case 0xf2:
        case 0xfa:
        case 0xea:
        case 0xe2:
            inst_jmp(state);
            break;

        case 0xcd:
            inst_call(state);
            break;

        default:
            print_state(state);
            disassemble8080(state);
            unimplementedInstruction(state);
            break;
    }

#ifdef __debug
    if (state->n_instructions > 50)
        getchar();
#endif

    state->n_instructions++;
}