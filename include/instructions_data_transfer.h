#ifndef INSTRUCTIONS_DATA_TRANSFER_H
#define INSTRUCTIONS_DATA_TRANSFER_H

#include "types.h"

void inst_lxi(State8080* state);
void inst_mvi(State8080* state);
void inst_ldax(State8080* state);
void inst_mov(State8080* state);
void inst_xchg(State8080* state);
void inst_lda(State8080* state);
void inst_sta(State8080* state);

// Yet to be implemented
void inst_lhld(State8080* state);
void inst_shld(State8080* state);
void inst_stax(State8080* state);

#endif