#include "Interpreter.h"

#ifdef Debugging
    #define Parameters\
        uint32_t Instruction __attribute__((unused)) = *ProgamCounter;\
        uint8_t Rd __attribute__((unused)) = (Instruction >> 11) & 0x1F;\
        uint8_t Rt __attribute__((unused)) = (Instruction >> 16) & 0x1F;\
        uint8_t Rs __attribute__((unused)) = (Instruction >> 21) & 0x1F;\
        uint8_t Shift __attribute__((unused)) = (Instruction >> 6) & 0x1F;\
        uint8_t Function __attribute__((unused)) = Instruction & 0x3F;\
        uint16_t Immediate __attribute__((unused)) = Instruction & 0xFFFF;\
        uint32_t Address __attribute__((unused)) = Instruction & 0x3FFFFFF;\
        RegisterUnsigned _Rd __attribute__((unused)) = GeneralPurpose[Rd];\
        RegisterUnsigned _Rt __attribute__((unused)) = GeneralPurpose[Rt];\
        RegisterUnsigned _Rs __attribute__((unused)) = GeneralPurpose[Rs];
#else
    #define Parameters\
        uint32_t Instruction __attribute__((unused)) = *ProgamCounter;\
        uint8_t Rd __attribute__((unused)) = (Instruction >> 11) & 0x1F;\
        uint8_t Rt __attribute__((unused)) = (Instruction >> 16) & 0x1F;\
        uint8_t Rs __attribute__((unused)) = (Instruction >> 21) & 0x1F;\
        uint8_t Shift __attribute__((unused)) = (Instruction >> 6) & 0x1F;\
        uint8_t Function __attribute__((unused)) = Instruction & 0x3F;\
        uint16_t Immediate __attribute__((unused)) = Instruction & 0xFFFF;\
        uint32_t Address __attribute__((unused)) = Instruction & 0x3FFFFFF
#endif

#ifdef Debugging
    #define Assembly(...) \
        {\
            printf( __VA_ARGS__ );\
            if(_Rd != GeneralPurpose[Rd] || _Rt != GeneralPurpose[Rt] || _Rs != GeneralPurpose[Rs])\
            {\
                printf("\nUpdated registers: \n");\
                if(_Rd != GeneralPurpose[Rd])\
                    printf("    %s = %lld\n", RegisterNames[Rd], GeneralPurpose[Rd]);\
                \
                if(_Rt != GeneralPurpose[Rt] && Rt != Rd)\
                    printf("    %s = %lld\n", RegisterNames[Rt], GeneralPurpose[Rt]);\
                \
                if(_Rs != GeneralPurpose[Rs] && Rs != Rd && Rs != Rt)\
                    printf("    %s = %lld\n", RegisterNames[Rs], GeneralPurpose[Rs]);\
            }\
        }
#endif

bool Branching;

void CPUUnknownOpCode()
{
    Parameters;

    printf("<unknown>\n\n");

    printf("    Opcode: 0x%.2X, Rs: 0x%.2X, Rt: 0x%.2X, Rd: 0x%.2X, Shift: 0x%.2X, Func: 0x%.2X\n", *ProgamCounter >> 26, Rs, Rt, Rd, Shift, Function);

    printf("    Opcode: 0x%.2X, Rs: 0x%.2X, Rt: 0x%.2X, Immediate: 0x%.4X\n", *ProgamCounter >> 26, Rs, Rt, Immediate);

    printf("    Opcode: 0x%.2X, Address: %9d\n", *ProgamCounter >> 26, Address);
}

void CPUNoOpCode()
{
    CPUUnknownOpCode();
}

#include "Interpreter/Arithmetic.inc"
#include "Interpreter/Arithmetic32.inc"
#include "Interpreter/Arithmetic64.inc"

VoidCall OpCode_0_Table[64];

void OpCode_0()
{
    Parameters;

    OpCode_0_Table[Function]();
}

VoidCall CPUJumpTable[64];

void CPUSetupJumpTables()
{
    // Main jumptable
    for(int i = 0;  i < 64; i++)
        CPUJumpTable[i] = CPUNoOpCode;

    // Opcode 0 jumptable
    for(int i = 0;  i < 64; i++)
        OpCode_0_Table[i] = CPUNoOpCode;

    CPUJumpTable[0] = OpCode_0;

    // Arithmetic Opcodes
    OpCode_0_Table[32] = AddTrap32;
    CPUJumpTable[8] = AddImmediateTrap32;
    CPUJumpTable[9] = AddImmediate32;
    OpCode_0_Table[33] = Add32;

    OpCode_0_Table[36] = And;
    CPUJumpTable[12] = AndImmediate;

    OpCode_0_Table[44] = AddTrap64;
    CPUJumpTable[24] = AddImmediateTrap64;
    CPUJumpTable[25] = AddImmediate64;
    OpCode_0_Table[45] = Add64;

    OpCode_0_Table[26] = Divide64;
    OpCode_0_Table[27] = DivideUnsigned64;

    OpCode_0_Table[30] = Divide32;
    OpCode_0_Table[31] = DivideUnsigned32;

    OpCode_0_Table[28] = Multiply64;
    OpCode_0_Table[29] = MultiplyUnsigned64;

    OpCode_0_Table[56] = ShiftLeftLogical64;
    OpCode_0_Table[60] = ShiftLeftLogical3264;
    OpCode_0_Table[20] = ShiftLeftLogicalVariable64;

    OpCode_0_Table[59] = ShiftRightArithmetic64;
    OpCode_0_Table[63] = ShiftRightArithmetic3264;
    OpCode_0_Table[23] = ShiftRightArithmeticVariable64;

    OpCode_0_Table[58] = ShiftRightLogical64;
    OpCode_0_Table[62] = ShiftRightLogical3264;
    OpCode_0_Table[22] = ShiftRightLogicalVariable64;

    OpCode_0_Table[46] = SubtractTrap64;
    OpCode_0_Table[47] = Subtract64;

    CPUJumpTable[15] = LoadUpperImmediate;

    OpCode_0_Table[16] = MoveFromHigh;
    OpCode_0_Table[18] = MoveFromLow;
    OpCode_0_Table[17] = MoveToHigh;
    OpCode_0_Table[19] = MoveToLow;

    OpCode_0_Table[24] = Multiply32;
    OpCode_0_Table[25] = MultiplyUnsigned32;

    OpCode_0_Table[39] = Nor;

    OpCode_0_Table[37] = Or;
    CPUJumpTable[13] = OrImmediate;

    OpCode_0_Table[0] = ShiftLeftLogical32;
    OpCode_0_Table[4] = ShiftLeftLogicalVariable32;

    OpCode_0_Table[42] = SetOnLessThan;
    CPUJumpTable[10] = SetOnLessThanImmediate;
    CPUJumpTable[11] = SetOnLessThanImmediateUnsigned;
    OpCode_0_Table[43] = SetOnLessThanUnsigned;

    OpCode_0_Table[3] = ShiftRightArithmetic32;
    OpCode_0_Table[7] = ShiftRightArithmeticVariable32;

    OpCode_0_Table[2] = ShiftRightLogical32;
    OpCode_0_Table[6] = ShiftRightLogicalVariable32;

    OpCode_0_Table[34] = SubtractTrap32;
    OpCode_0_Table[35] = Subtract32;

    OpCode_0_Table[38] = Xor;
    CPUJumpTable[14] = XorImmediate;
}
