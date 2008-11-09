void And()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) & GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("and %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void AndImmediate()
{
    Parameters;

    GeneralPurpose64(Rt) = GeneralPurpose64(Rs) & Immediate;

    if(Debugging)
        Assembly("andi %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void LoadUpperImmediate()
{
    Parameters;

    ((uint16_t*)(&GeneralPurpose[Rt]))[1] = Immediate;

    if(Debugging)
        Assembly("lui %s, %d\n", RegisterNames[Rt], Immediate);
}

void MoveFromHigh()
{
    Parameters;

    GeneralPurpose64(Rd) = RegHigh64;

    if(Debugging)
        Assembly("mfhi %s\n", RegisterNames[Rd]);
}

void MoveFromLow()
{
    Parameters;

    GeneralPurpose64(Rd) = RegLow64;

    if(Debugging)
        Assembly("mflo %s\n", RegisterNames[Rd]);
}

void MoveToHigh()
{
    Parameters;

    RegHigh64 = GeneralPurpose64(Rd);

    if(Debugging)
        Assembly("mthi %s\n", RegisterNames[Rd]);
}

void MoveToLow()
{
    Parameters;

    RegLow64 = GeneralPurpose64(Rd);

    if(Debugging)
        Assembly("mtlo %s\n", RegisterNames[Rd]);
}

void Nor()
{
    Parameters;

    GeneralPurpose64(Rd) = !(GeneralPurpose64(Rs) | GeneralPurpose64(Rt));

    if(Debugging)
        Assembly("nor %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Or()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) | GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("or %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void OrImmediate()
{
    Parameters;

    GeneralPurpose64(Rt) = GeneralPurpose64(Rs) | Immediate;

    if(Debugging)
        Assembly("ori %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void SetOnLessThan()
{
    Parameters;

    if((int64_t)GeneralPurpose64(Rs) < (int64_t)GeneralPurpose64(Rt))
        GeneralPurpose64(Rd) = 1;
    else
        GeneralPurpose64(Rd) = 0;

    if(Debugging)
        Assembly("slt %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void SetOnLessThanImmediate()
{
    Parameters;

    if((int64_t)GeneralPurpose64(Rs) < (int16_t)Immediate)
        GeneralPurpose64(Rd) = 1;
    else
        GeneralPurpose64(Rd) = 0;

    if(Debugging)
        Assembly("slti %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void SetOnLessThanImmediateUnsigned()
{
    Parameters;

    if(GeneralPurpose64(Rs) < Immediate)
        GeneralPurpose64(Rd) = 1;
    else
        GeneralPurpose64(Rd) = 0;

    if(Debugging)
        Assembly("sltiu %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}

void SetOnLessThanUnsigned()
{
    Parameters;

    if(GeneralPurpose64(Rs) < GeneralPurpose64(Rt))
        GeneralPurpose64(Rd) = 1;
    else
        GeneralPurpose64(Rd) = 0;

    if(Debugging)
        Assembly("sltu %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void Xor()
{
    Parameters;

    GeneralPurpose64(Rd) = GeneralPurpose64(Rs) ^ GeneralPurpose64(Rt);

    if(Debugging)
        Assembly("xor %s, %s, %s\n", RegisterNames[Rd], RegisterNames[Rs], RegisterNames[Rt]);
}

void XorImmediate()
{
    Parameters;

    GeneralPurpose64(Rt) = GeneralPurpose64(Rs) ^ Immediate;

    if(Debugging)
        Assembly("xori %s, %s, %d\n", RegisterNames[Rt], RegisterNames[Rs], Immediate);
}
