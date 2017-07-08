#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct
{
    uint8_t z:1;
    uint8_t s:1;
    uint8_t p:1;
    uint8_t cy:1;
    uint8_t ac:1;
    uint8_t pad:3;
} ConditionCodes;

typedef struct
{
    // Registers
    uint8_t         a;
    uint8_t         b;
    uint8_t         c;
    uint8_t         d;
    uint8_t         e;
    uint8_t         h;
    uint8_t         l;
    uint16_t        sp;
    uint16_t        pc;

    // Memory
    uint8_t         *memory;

    // Flags
    uint8_t         int_enabled;
    ConditionCodes flags;

    // Other
    unsigned long long cycles;
    unsigned long long n_instructions;
} State8080;

#endif