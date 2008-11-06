#pragma once
#include <stdio.h>
#include "CPU.h"

#define CPUMakeRegisterOp(OpCode, Rs, Rt, Rd, Shift, Func) ((OpCode & 0x3F) << 26) | ((Rs & 0x1F) << 21) | ((Rt & 0x1F) << 16) | ((Rd & 0x1F) << 11) | ((Shift & 0x1F) << 6) | (Func & 0x3F)
#define CPUMakeImmediateOp(OpCode, Rs, Rt, Immediate) ((OpCode & 0x3F) << 26) | ((Rs & 0x1F) << 21) | ((Rt & 0x1F) << 16) | (Immediate & 0xFFFF)

typedef void (*VoidCall)();
extern VoidCall CPUJumpTable[64];

void CPUSetupJumpTables();
void CPUUnknownOpCode();
void CPUNoOpCode();

