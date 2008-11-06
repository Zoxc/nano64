void AddTrap32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rs) + GeneralPurpose32(Rt);

    if(Debugging)
        Assembly("add %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void AddImmediateTrap32()
{
    Parameters;

    GeneralPurpose32(Rt) = GeneralPurpose32(Rs) + (int16_t)Immediate;

    if(Debugging)
        Assembly("addi %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void AddImmediate32()
{
    Parameters;

    GeneralPurpose32(Rt) = GeneralPurpose32(Rs) + Immediate;

    if(Debugging)
        Assembly("addiu %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void Add32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rs) + GeneralPurpose32(Rt);

    if(Debugging)
        Assembly("addu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Divide32()
{
    Parameters;

    RegLow32 = (uint32_t)((int32_t)GeneralPurpose32(Rs) / (int32_t)GeneralPurpose32(Rt));
    RegHigh32 = (uint32_t)((int32_t)GeneralPurpose32(Rs) % (int32_t)GeneralPurpose32(Rt));

    if(Debugging)
        Assembly("div %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void DivideUnsigned32()
{
    Parameters;

    RegLow32 = GeneralPurpose32(Rs) / GeneralPurpose32(Rt);
    RegHigh32 = GeneralPurpose32(Rs) % GeneralPurpose32(Rt);

    if(Debugging)
        Assembly("divu %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void Multiply32()
{
    Parameters;

    int64_t Result = (int32_t)GeneralPurpose32(Rs) * (int32_t)GeneralPurpose32(Rt);

    RegLow32 = Result;
    RegHigh32 = Result >> 32;

    if(Debugging)
        Assembly("mult %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void MultiplyUnsigned32()
{
    Parameters;

    uint64_t Result = GeneralPurpose32(Rs) * GeneralPurpose32(Rt);

    RegLow32 = Result;
    RegHigh32 = Result >> 32;

    if(Debugging)
        Assembly("multu %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void ShiftLeftLogical32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rt) << Shift;

    if(Debugging)
        Assembly("sll %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftLeftLogicalVariable32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rt) << GeneralPurpose32(Rs);

    if(Debugging)
        Assembly("sllv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void ShiftRightArithmetic32()
{
    Parameters;

    GeneralPurpose32(Rd) = (uint32_t)((int32_t)GeneralPurpose32(Rt) >> Shift);

    if(Debugging)
        Assembly("srl %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightArithmeticVariable32()
{
    Parameters;

    GeneralPurpose32(Rd) = (uint32_t)((int32_t)GeneralPurpose32(Rs) >> GeneralPurpose32(Rt));

    if(Debugging)
        Assembly("srlv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void ShiftRightLogical32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rt) >> Shift;

    if(Debugging)
        Assembly("srl %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightLogicalVariable32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rt) >> GeneralPurpose32(Rs);

    if(Debugging)
        Assembly("srlv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void SubtractTrap32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rs) - GeneralPurpose32(Rt);

    if(Debugging)
        Assembly("sub %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Subtract32()
{
    Parameters;

    GeneralPurpose32(Rd) = GeneralPurpose32(Rs) - GeneralPurpose32(Rt);

    if(Debugging)
        Assembly("subu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}
