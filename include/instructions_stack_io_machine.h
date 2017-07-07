#ifndef INSTRUCTIONS_STACK_IO_MACHINE_H
#define INSTRUCTIONS_STACK_IO_MACHINE_H

#include "types.h"

void inst_push(State8080* state);
void inst_pop(State8080* state);

// Yet to be implemented
void inst_xthl(State8080* state);
void inst_sphl(State8080* state);
void inst_in(State8080* state);
void inst_out(State8080* state);
void inst_ei(State8080* state);
void inst_di(State8080* state);
void inst_hlt(State8080* state);
void inst_nop(State8080* state);

#endif