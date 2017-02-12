#include "Screen.h"

void SCR_GotoXY(short x, short y)
{
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SCR_Clrscr(void)
{
    COORD coord = { 0,0 };
    DWORD write;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X * info.dwSize.Y, coord, &write);
    SCR_GotoXY(1, 1);
}

void SCR_SetTextColor(color_t color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    WORD attributes;

    GetConsoleScreenBufferInfo(hConsoleOutput, &info);

    attributes = info.wAttributes;
    attributes &= ~(0x000F);
    attributes |= (DWORD)color;
    
    SetConsoleTextAttribute(hConsoleOutput, attributes);
}

void SCR_SetBGColor(color_t color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    WORD attributes;

    GetConsoleScreenBufferInfo(hConsoleOutput, &info);

    attributes = info.wAttributes;
    attributes &= ~(0x00F0);
    attributes |= (DWORD)color << 4;

    SetConsoleTextAttribute(hConsoleOutput, attributes);
}

void SCR_Delay(int ms)
{
    Sleep(ms);
}

void SCR_NoCursorType()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
