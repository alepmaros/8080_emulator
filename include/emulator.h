#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"

void    unimplementedInstruction(State8080* state);
void    emulate8080(State8080* state);
#endif