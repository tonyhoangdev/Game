#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "Screen.h"
#include "Tetris.h"

int main()
{
    //HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //COORD coord = { 12, 23 };
    //SetConsoleCursorPosition(consoleHandle, coord);

    //SetConsoleTextAttribute(consoleHandle, 2);
    //SCR_NoCursorType();

    //g_board[5][6] = 1;
    //g_board[5][7] = 1;
    //g_board[5][8] = 1;
    //g_board[5][9] = 1;

    //g_board[7][6] = 1;
    //g_board[7][7] = 1;
    //g_board[8][6] = 1;
    //g_board[8][7] = 1;

    //g_board[10][6] = 1;
    //g_board[10][7] = 1;
    //g_board[10][8] = 1;
    //g_board[11][8] = 1;

    //DrawBoard();
    //DisplayBoard();

    //for (int i = 12; i < 22; i++)
    //{
    //    UpdateToaDo(i);
    //    Sleep(500);
    //    DisplayBoard();
    //}

    //info_t info;
    //InitGame(&info);
    //UpdateInfo(&info, 200);
    //DrawPointTable(info);

    //for (int i = 0; i < 16; i++)
    //{
    //    Clrscr();
    //    SetTextColor((color_t)i);
    //    SetBGColor(LIGHT_GREEN);
    //    GotoXY(5, 10);
    //    printf("Hello %d\n", i);
    //    printf("%c", 135);
    //    Delay(1000);
    //}

    int idKhoiNext;
    int loai, fix = 0;
    clock_t start, end;
    char c;
    info_t info;
    khoi_gach_t * currKhoi;
    int conti = 0;
START:
    rand();
    currKhoi = CreateKhoiGach(Loai());
    idKhoiNext = Loai();
    DrawBoard();
    InitGame(&info);
    SCR_NoCursorType();


    do
    {
        DrawPointTable(info);
        DrawKhoiGach(currKhoi);
        Xoa_Next();
        Ve_Next(idKhoiNext);
        start = clock();
        do
        {
            if (kbhit())
            {
                c = toupper(getch());
                DeleteKhoiGach(currKhoi);
                switch (c)
                {
                case 'W':
                    RotateValue(currKhoi);
                    break;
                case 'A':
                    MoveLeft(currKhoi);
                    break;
                case 'D':
                    MoveRight(currKhoi);
                    break;
                case 'S':
                    MoveDown(currKhoi);
                    break;
                case 'G':
                    fix = 1;
                    loai = 15;
                    break;
                case 'V':
                    fix = 1;
                    loai = 31;
                default:
                    /* Do nothing */
                    break;
                }
                DrawKhoiGach(currKhoi);
            }
            end = clock();
        } while (((float)(end - start) / CLOCKS_PER_SEC) < info.speed);
        DeleteKhoiGach(currKhoi);
        if (MoveDown(currKhoi) == 0)
        {
            SetValue(currKhoi);
            int ketqua = Check(currKhoi, &info);
            if (ketqua == -1 || ketqua == 0)
            {
                break;
            }
            HuyKhoiGach(currKhoi);
            currKhoi = CreateKhoiGach(idKhoiNext);
            idKhoiNext = Loai();
            if (fix == 1)
            {
                fix = 0;
                idKhoiNext = loai;
            }
        }
        DisplayBoard();
    } while (true);
    SCR_SetTextColor(GREEN);
    SCR_GotoXY(35, 20);
    printf("End game. Press 't' key to exit.");
    do
    {
        SCR_Delay(500);
        SCR_GotoXY(35, 20);
        printf("                                ");
        SCR_Delay(500);
        SCR_GotoXY(35, 20);
        printf("End game. Press 't' key to exit.");
        if (getch() == 't')
        {
            break;
        }
        if (getch() == 'c')
        {
            conti = 1;
            break;
        }

    } while (true);

    if (conti == 1)
    {
        conti = 0;
        goto START;
    }

    return 0;
}
