#pragma once
#include <stdio.h>
#include <inttypes.h>
#include "CPU.h"

#define Debugging true

#define MakeRegisterOp(OpCode, Rs, Rt, Rd, Shift, Func) ((OpCode & 0x3F) << 26) | ((Rs & 0x1F) << 21) | ((Rt & 0x1F) << 16) | ((Rd & 0x1F) << 11) | ((Shift & 0x1F) << 6) | (Func & 0x3F)
#define MakeImmediateOp(OpCode, Rs, Rt, Immediate) ((OpCode & 0x3F) << 26) | ((Rs & 0x1F) << 21) | ((Rt & 0x1F) << 16) | (Immediate & 0xFFFF)

typedef void (*VoidCall)();
extern VoidCall JumpTable[64];

void SetupJumpTable();
void UnknownOpCode();
void NoOpCode();

