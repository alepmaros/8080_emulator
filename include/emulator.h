#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"

void    unimplementedInstruction(State8080* state);
void    emulate8080(State8080* state);
void    loadRomToMemory(char* fname, State8080* state);

State8080* initializeState8080();

#endif