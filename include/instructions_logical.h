#ifndef INSTRUCTIONS_LOGICAL_H
#define INSTRUCTIONS_LOGICAL_H

#include "types.h"

void inst_cpi(State8080* state);

// Yet to be implemented
void inst_ana(State8080* state);
void inst_ani(State8080* state);
void inst_xra(State8080* state);
void inst_xri(State8080* state);
void inst_ora(State8080* state);
void inst_ori(State8080* state);
void inst_cmp(State8080* state);
void inst_rlc(State8080* state);
void inst_rrc(State8080* state);
void inst_ral(State8080* state);
void inst_rar(State8080* state);
void inst_cma(State8080* state);
void inst_cmc(State8080* state);
void inst_stc(State8080* state);

#endif