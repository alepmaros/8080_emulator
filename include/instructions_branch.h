#ifndef INSTRUCTIONS_BRANCH_H
#define INSTRUCTIONS_BRANCH_H

#include "types.h"

void inst_jmp(State8080* state);

// Yet to be implemented
void inst_jc(State8080* state);
void inst_call(State8080* state);
void inst_cc(State8080* state);
void inst_ret(State8080* state);
void inst_rc(State8080* state);
void inst_rst(State8080* state);
void inst_pchl(State8080* state);

#endif