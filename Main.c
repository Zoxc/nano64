#include <stdlib.h>
#include <conio.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include "CPU\CPU.h"
#include "CPU\OpCodes.h"

void WaitForKeyPress()
{
    _getch();
}

void ClearScreen()
{
    #ifdef WIN32
        HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD Coord = {0, 0};
        DWORD Count;

        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(StdOut, &Info);

        FillConsoleOutputCharacter(StdOut, ' ', Info.dwSize.X * Info.dwSize.Y, Coord, &Count);

        SetConsoleCursorPosition(StdOut, Coord);
    #else
        write(1,"\E[H\E[2J",7);
    #endif
}

void DumpRegisters()
{
    int Align = 0;
    for(int i = 0; i < 33; i++, Align++)
    {
        if(i == 32)
            printf("$pc: %.8X", (uint32_t)ProgamCounter);
        else
            printf("%s: %16lld", RegisterNames[i], GeneralPurpose[i]);

        if(Align == 2)
        {
            Align = -1;
            printf("\n");
        }
        else
            printf("        ");
    }
}

void Intrepret()
{
    GeneralPurpose[0] = 0;

    if(Debugging)
    {
        while(true)
        {
            uint32_t Instruction = *ProgamCounter;

            ClearScreen();
            printf("nano64 0.0.1 - A very incomplete Nintendo 64 emulator %X\n\n", MakeImmediateOp(0x9, 0, 2, 1337));

            DumpRegisters();

            printf("\n\nCurrent instruction [%.8X] ", Instruction);

            JumpTable[Instruction >> 26]();

            printf("\nPress a key to step forward...");

            WaitForKeyPress();

            ProgamCounter++;
        }

        ClearScreen();
        printf("nano64 0.0.1 - A very incomplete Nintendo 64 emulator\n\n");

        DumpRegisters();

        printf("\n\nEmulation done. Press a key to quit.");

        WaitForKeyPress();
    }
    else
    {
        while(true)
        {
            uint32_t Instruction = *ProgamCounter;

            JumpTable[Instruction >> 26]();

            ProgamCounter++;
        }
    }
}

int main()
{
    printf("nano64 0.0.1 - A very incomplete Nintendo 64 emulator\n");

    SetupJumpTables();

    uint32_t Test[] = {MakeImmediateOp(0x9, 0, 2, 0x1337), MakeRegisterOp(0, 3, 2, 1, 0, 0x21), MakeRegisterOp(0, 0, 1, 3, 2, 0x23), 0};

    ProgamCounter = Test;

    Intrepret();

    return 0;
}
