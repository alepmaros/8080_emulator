#ifndef UTILS_H
#define UTILS_H

#include "types.h"

void    unimplementedInstruction(State8080* state);
int     parity(uint8_t num);
void    print_state(State8080* state);

#endif