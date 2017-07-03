#ifndef INSTRUCTIONS_ARITHMETIC_H
#define INSTRUCTIONS_ARITHMETIC_H

#include "emulator.h"

void inst_add(State8080* state);
void inst_adi(State8080* state);
void inst_adc(State8080* state);

#endif