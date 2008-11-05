#include "OpCodes.h"

#ifdef Debugging
    #define Parameters\
        uint8_t Rd __attribute__((unused)) = (*ProgamCounter >> 11) & 0x1F;\
        uint8_t Rt __attribute__((unused)) = (*ProgamCounter >> 16) & 0x1F;\
        uint8_t Rs __attribute__((unused)) = (*ProgamCounter >> 21) & 0x1F;\
        uint8_t Shift __attribute__((unused)) = (*ProgamCounter >> 6) & 0x1F;\
        uint8_t Function __attribute__((unused)) = *ProgamCounter & 0x3F;\
        uint16_t Immediate __attribute__((unused)) = *ProgamCounter & 0xFFFF;\
        uint32_t Address __attribute__((unused)) = *ProgamCounter & 0x3FFFFFF;\
        RegisterUnsigned _Rd __attribute__((unused)) = GeneralPurpose[Rd];\
        RegisterUnsigned _Rt __attribute__((unused)) = GeneralPurpose[Rt];\
        RegisterUnsigned _Rs __attribute__((unused)) = GeneralPurpose[Rs];
#else
    #define Parameters\
        uint8_t Rd __attribute__((unused)) = (*ProgamCounter >> 11) & 0x1F;\
        uint8_t Rt __attribute__((unused)) = (*ProgamCounter >> 16) & 0x1F;\
        uint8_t Rs __attribute__((unused)) = (*ProgamCounter >> 21) & 0x1F;\
        uint8_t Shift __attribute__((unused)) = (*ProgamCounter >> 6) & 0x1F;\
        uint8_t Function __attribute__((unused)) = *ProgamCounter & 0x3F;\
        uint16_t Immediate __attribute__((unused)) = *ProgamCounter & 0xFFFF;\
        uint32_t Address __attribute__((unused)) = *ProgamCounter & 0x3FFFFFF
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

void UnknownOpCode()
{
    Parameters;

    printf("<unknown>\n\n");

    printf("    Opcode: 0x%.2X, Rs: 0x%.2X, Rt: 0x%.2X, Rd: 0x%.2X, Shift: 0x%.2X, Func: 0x%.2X\n", *ProgamCounter >> 26, Rs, Rt, Rd, Shift, Function);

    printf("    Opcode: 0x%.2X, Rs: 0x%.2X, Rt: 0x%.2X, Immediate: 0x%.4X\n", *ProgamCounter >> 26, Rs, Rt, Immediate);

    printf("    Opcode: 0x%.2X, Address: %9d\n", *ProgamCounter >> 26, Address);
}

void NoOpCode()
{
    UnknownOpCode();
}

void MoveFromHigh()
{
    Parameters;

    GeneralPurpose[Rd] = RegHigh;

    if(Debugging)
        Assembly("mfhi %s\n", RegisterNames[Rd]);
}

void MoveFromLow()
{
    Parameters;

    GeneralPurpose[Rd] = RegLow;

    if(Debugging)
        Assembly("mflo %s\n", RegisterNames[Rd]);
}

void Add()
{
    Parameters;

    GeneralPurpose[Rd] = GeneralPurpose[Rs] + GeneralPurpose[Rt];

    if(Debugging)
        Assembly("addu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void AddTrap()
{
    Parameters;

    GeneralPurpose[Rd] = GeneralPurpose[Rs] + GeneralPurpose[Rt];

    if(Debugging)
        Assembly("add %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void SubtractTrap()
{
    Parameters;

    GeneralPurpose[Rd] = GeneralPurpose[Rs] - GeneralPurpose[Rt];

    if(Debugging)
        Assembly("sub %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Subtract()
{
    Parameters;

    GeneralPurpose[Rd] = GeneralPurpose[Rs] - GeneralPurpose[Rt];

    if(Debugging)
        Assembly("subu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Multiply()
{
    Parameters;

    ((uint32_t*)&RegLow)[0] = ((uint32_t*)&GeneralPurpose[Rs])[0] * ((uint32_t*)&GeneralPurpose[Rt])[0];
    ((uint32_t*)&RegLow)[1] = ((uint32_t*)&GeneralPurpose[Rs])[0] * ((uint32_t*)&GeneralPurpose[Rt])[1];

    ((uint32_t*)&RegHigh)[0] = ((uint32_t*)&GeneralPurpose[Rs])[1] * ((uint32_t*)&GeneralPurpose[Rt])[0];
    ((uint32_t*)&RegHigh)[1] = ((uint32_t*)&GeneralPurpose[Rs])[1] * ((uint32_t*)&GeneralPurpose[Rt])[1];

    if(Debugging)
        Assembly("mult %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void Divide()
{
    Parameters;

    RegLow = (uint64_t)((int64_t)GeneralPurpose[Rs] / (int64_t)GeneralPurpose[Rt]);
    RegHigh = (uint64_t)((int64_t)GeneralPurpose[Rs] % (int64_t)GeneralPurpose[Rt]);

    if(Debugging)
        Assembly("div %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void DivideUnsigned() // mult RegLow, RegHigh = Rs * Rt
{
    Parameters;

    RegLow = GeneralPurpose[Rs] / GeneralPurpose[Rt];
    RegHigh = GeneralPurpose[Rs] % GeneralPurpose[Rt];

    if(Debugging)
        Assembly("divu %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void OpCode_0()
{
    Parameters;

    switch(Function)
    {
        case 0:
            if(Debugging)
                Assembly("nop\n");
            break;

        case 0x10: MoveFromHigh(); break;
        case 0x12: MoveFromLow(); break;

        case 0x18: Multiply(); break;

        case 0x1A: Divide(); break;
        case 0x1B: DivideUnsigned(); break;

        case 0x20: AddTrap(); break;
        case 0x21: Add(); break;

        case 0x22: SubtractTrap(); break;
        case 0x23: Subtract(); break;

        default: UnknownOpCode(); break;
    }
}

void AddImmediateTrap()
{
    Parameters;

    GeneralPurpose[Rt] = GeneralPurpose[Rs] + (RegisterSigned)Immediate;

    if(Debugging)
        Assembly("addi %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void AddImmediate()
{
    Parameters;

    GeneralPurpose[Rt] = GeneralPurpose[Rs] + (RegisterSigned)Immediate;

    if(Debugging)
        Assembly("addiu %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

VoidCall JumpTable[64];

void SetupJumpTable()
{
    for(int i = 0;  i < 64; i++)
        JumpTable[i] = NoOpCode;

    JumpTable[0] = OpCode_0;
    JumpTable[0x8] = AddImmediateTrap;
    JumpTable[0x9] = AddImmediate;
}
