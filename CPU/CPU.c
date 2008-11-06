#include "CPU.h"

const char* RegisterNames[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

uint64_t GeneralPurpose[64];
uint64_t FPGeneralPurpose[64];
uint32_t* ProgamCounter;

uint64_t RegHigh;
uint64_t RegLow;

bool LLbit;
