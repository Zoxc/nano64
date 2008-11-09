void AddTrap64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) + GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("dadd %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void AddImmediateTrap64()
{
    Parameters;

    GeneralPurpose64(Rt) = GeneralPurpose64(Rs) + (int16_t)Immediate;

    if(Debugging)
        Assembly("daddi %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void AddImmediate64()
{
    Parameters;

    GeneralPurpose64(Rt) = GeneralPurpose64(Rs) + Immediate;

    if(Debugging)
        Assembly("daddiu %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void Add64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) + GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("daddu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Divide64()
{
    Parameters;

    RegLow64 = (uint64_t)((int64_t)GeneralPurpose64(Rs) / (int64_t)GeneralPurpose64(Rt));
    RegHigh64 = (uint64_t)((int64_t)GeneralPurpose64(Rs) % (int64_t)GeneralPurpose64(Rt));

    if(Debugging)
        Assembly("ddiv %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void DivideUnsigned64()
{
    Parameters;

    RegLow64 = GeneralPurpose64(Rs) / GeneralPurpose64(Rt);
    RegHigh64 = GeneralPurpose64(Rs) % GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("ddivu %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void Multiply64()
{
    Parameters;

    unsigned long long int op1, op2, op3, op4;
    unsigned long long int result1, result2, result3, result4;
    unsigned long long int temp1, temp2, temp3, temp4;
    int sign = 0;

    if (GeneralPurpose64(Rs) < 0)
    {
        op2 = -GeneralPurpose64(Rs);
        sign = 1 - sign;
    }
    else
        op2 = GeneralPurpose64(Rs);

    if (GeneralPurpose64(Rt) < 0)
    {
        op4 = -GeneralPurpose64(Rt);
        sign = 1 - sign;
    }
    else
        op4 = GeneralPurpose64(Rt);

    op1 = op2 & 0xFFFFFFFF;
    op2 = (op2 >> 32) & 0xFFFFFFFF;
    op3 = op4 & 0xFFFFFFFF;
    op4 = (op4 >> 32) & 0xFFFFFFFF;

    temp1 = op1 * op3;
    temp2 = (temp1 >> 32) + op1 * op4;
    temp3 = op2 * op3;
    temp4 = (temp3 >> 32) + op2 * op4;

    result1 = temp1 & 0xFFFFFFFF;
    result2 = temp2 + (temp3 & 0xFFFFFFFF);
    result3 = (result2 >> 32) + temp4;
    result4 = (result3 >> 32);

    RegLow64 = result1 | (result2 << 32);
    RegHigh64 = (result3 & 0xFFFFFFFF) | (result4 << 32);
    if (sign)
    {
        RegHigh64 = ~RegHigh64;
        if(!RegLow64)
            RegHigh64++;
        else RegLow64 = ~RegLow64 + 1;
    }

    if(Debugging)
        Assembly("dmult %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void MultiplyUnsigned64()
{
    Parameters;

    unsigned long long int op1, op2, op3, op4;
    unsigned long long int result1, result2, result3, result4;
    unsigned long long int temp1, temp2, temp3, temp4;

    op1 = GeneralPurpose64(Rs) & 0xFFFFFFFF;
    op2 = (GeneralPurpose64(Rs) >> 32) & 0xFFFFFFFF;
    op3 = GeneralPurpose64(Rt) & 0xFFFFFFFF;
    op4 = (GeneralPurpose64(Rt) >> 32) & 0xFFFFFFFF;

    temp1 = op1 * op3;
    temp2 = (temp1 >> 32) + op1 * op4;
    temp3 = op2 * op3;
    temp4 = (temp3 >> 32) + op2 * op4;

    result1 = temp1 & 0xFFFFFFFF;
    result2 = temp2 + (temp3 & 0xFFFFFFFF);
    result3 = (result2 >> 32) + temp4;
    result4 = (result3 >> 32);

    RegLow64 = result1 | (result2 << 32);
    RegHigh64 = (result3 & 0xFFFFFFFF) | (result4 << 32);

    if(Debugging)
        Assembly("dmultu %s, %s\n", RegisterNames[Rs], RegisterNames[Rt]);
}

void ShiftLeftLogical64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) << Shift;

    if(Debugging)
        Assembly("dsll %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftLeftLogical3264()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) << (Shift + 32);

    if(Debugging)
        Assembly("dsll32 %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftLeftLogicalVariable64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) << GeneralPurpose64(Rs);

    if(Debugging)
        Assembly("dsllv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void ShiftRightArithmetic64()
{
    Parameters;

    GeneralPurpose64(Rd) = (uint64_t)((int64_t)GeneralPurpose64(Rt) >> Shift);

    if(Debugging)
        Assembly("dsrl %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightArithmetic3264()
{
    Parameters;

    GeneralPurpose64(Rd) = (uint64_t)((int64_t)GeneralPurpose64(Rt) >> (Shift + 32));

    if(Debugging)
        Assembly("dsrl32 %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightArithmeticVariable64()
{
    Parameters;

    GeneralPurpose64(Rd) = (uint64_t)((int64_t)GeneralPurpose64(Rs) >> GeneralPurpose64(Rt));

    if(Debugging)
        Assembly("dsrlv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void ShiftRightLogical64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) >> Shift;

    if(Debugging)
        Assembly("dsrl %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightLogical3264()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) >> (Shift + 32);

    if(Debugging)
        Assembly("dsrl32 %s, %s, %d\n", RegisterNames[Rd], RegisterNames[Rt], Shift);
}

void ShiftRightLogicalVariable64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rt) >> GeneralPurpose64(Rs);

    if(Debugging)
        Assembly("dsrlv %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rt], RegisterNames[Rs]);
}

void SubtractTrap64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) - GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("dsub %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Subtract64()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) - GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("dsubu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}
