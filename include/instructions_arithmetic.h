#ifndef INSTRUCTIONS_ARITHMETIC_H
#define INSTRUCTIONS_ARITHMETIC_H

#include "emulator.h"

void inst_add(State8080* state);
void inst_adi(State8080* state);
void inst_adc(State8080* state);
void inst_aci(State8080* state);
void inst_inx(State8080* state);
void inst_dcr(State8080* state);
void inst_dad(State8080* state);

// Yet to be implemented
void inst_sub(State8080* state);
void inst_sui(State8080* state);
void inst_sbb(State8080* state);
void inst_sbi(State8080* state);
void inst_inr(State8080* state);
void inst_dcx(State8080* state);
void inst_daa(State8080* state);

#endif