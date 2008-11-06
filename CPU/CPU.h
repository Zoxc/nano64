#pragma once
#include <stdbool.h>
#include <stdint.h>

extern const char* RegisterNames[32];

typedef uint64_t RegisterUnsigned;
typedef int64_t RegisterSigned;

#define GeneralPurpose32(Index) (*(uint32_t*)(&GeneralPurpose[Index]))
#define GeneralPurpose64(Index) GeneralPurpose[Index]

extern RegisterUnsigned GeneralPurpose[64];
extern RegisterUnsigned FPGeneralPurpose[64];
extern uint32_t* ProgamCounter;

extern RegisterUnsigned RegHigh;
extern RegisterUnsigned RegLow;

extern bool LLbit;
