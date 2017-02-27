#include "Tetris.h"

int g_board[MAX_ROW][MAX_COL] = { 0 };

void DrawBoard(void)
{
    int i, j;
    for (i = LEFT; i <= LEFT + 10 + 1; i++)
    {
        for (j = TOP; j <= TOP + 18 + 1; j++)
        {
            if ((j == TOP || j == TOP + 18 + 1) && i > LEFT && i < LEFT + 10 + 1)
            {
                SCR_GotoXY(i, j);
                SCR_SetTextColor(WHITE);
                printf("%c", 205);
            }
            if ((i == LEFT || i == LEFT + 10 + 1) && j > TOP && j < TOP + 18 + 1)
            {
                SCR_GotoXY(i, j);
                SCR_SetTextColor(WHITE);
                printf("%c", 186);
            }
        }

        SCR_GotoXY(LEFT, TOP);
        SCR_SetTextColor(LIGHT_RED);
        printf("%c", 219);

        SCR_GotoXY(LEFT + 10 + 1, TOP);
        SCR_SetTextColor(LIGHT_RED);
        printf("%c", 219);

        SCR_GotoXY(LEFT, TOP + 18 + 1);
        SCR_SetTextColor(LIGHT_RED);
        printf("%c", 219);

        SCR_GotoXY(LEFT + 10 + 1, TOP + 18 + 1);
        SCR_SetTextColor(LIGHT_RED);
        printf("%c", 219);
    }
}

void DisplayBoard(void)
{
    int i, j;
    for (i = 0; i < MAX_ROW; i++)
    {
        for (j = 0; j < MAX_COL; j++)
        {
            if (g_board[i][j] == 1 && i >= 4)
            {
                SCR_GotoXY(j + LEFT + 1, i + TOP + 1 - 4);
                SCR_SetTextColor(LIGHT_WHITE);
                printf("%c", 2);
            }
            if (g_board[i][j] == 0 && i >= 4)
            {
                SCR_GotoXY(j + LEFT + 1, i + TOP + 1 - 4);
                SCR_SetTextColor(BLACK);
                printf(" ");


            }
        }
    }
}

void UpdateToaDo(int row)
{
    int i, j;
    for (i = row; i > 0; i--)
    {
        for (j = 0; j < MAX_COL; j++)
        {
            g_board[i][j] = g_board[i - 1][j];
        }
    }
}

khoi_gach_t * CreateKhoiGach(int id)
{
    khoi_gach_t * pKhoiGach = (khoi_gach_t *)malloc(sizeof(khoi_gach_t));

    switch (id)
    {
    case 15:
        pKhoiGach->row = 4;
        pKhoiGach->col = 1;
        pKhoiGach->iBoard = 0;
        pKhoiGach->jBoard = 5;
        break;
    case 31:
        pKhoiGach->row = 2;
        pKhoiGach->col = 2;
        pKhoiGach->iBoard = 2;
        pKhoiGach->jBoard = 5;
        break;
    default:
        pKhoiGach->row = 2;
        pKhoiGach->col = 3;
        pKhoiGach->iBoard = 2;
        pKhoiGach->jBoard = 5;
        break;
    }
    pKhoiGach->arr = (int**)malloc(pKhoiGach->row * sizeof(int*));
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        pKhoiGach->arr[i] = (int*)malloc(pKhoiGach->col * sizeof(int));
    }
    for (int j = 0; j < pKhoiGach->col * pKhoiGach->row; j++)
    {
        pKhoiGach->arr[j / pKhoiGach->col][j  %pKhoiGach->col] = (id >> (pKhoiGach->col * pKhoiGach->row - 1 - j) & 1);
    }

    return pKhoiGach;
}

int Inside(int x, int y)
{
    return ((x >= 0) && (x < MAX_ROW) && (y >= 0) && (y < MAX_COL));
}

int Left(int x, int y)
{
    if ((y > 0) && Inside(x, y) && (g_board[x][y - 1] == 0))
    {
        return 1;
    }

    return 0;
}
int Right(int x, int y)
{
    if ((y < MAX_COL - 1) && Inside(x, y) && (g_board[x][y + 1] == 0))
    {
        return 1;
    }

    return 0;
}

int Down(int x, int y)
{
    if ((x < MAX_ROW - 1) && Inside(x, y) && (g_board[x + 1][y] == 0))
    {
        return 1;
    }

    return 0;
}

void MoveLeft(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1)
            {
                if (Left(pKhoiGach->iBoard + i, pKhoiGach->jBoard + j) == 0 || pKhoiGach->iBoard <= 3) return;
            }
        }
    }

    pKhoiGach->jBoard -= 1;
}

void MoveRight(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1)
            {
                if (Right(pKhoiGach->iBoard + i, pKhoiGach->jBoard + j) == 0 || pKhoiGach->iBoard <= 3) return;
            }
        }
    }

    pKhoiGach->jBoard += 1;
}

int MoveDown(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1)
            {
                if (Down(pKhoiGach->iBoard + i, pKhoiGach->jBoard + j) == 0) return 0;
            }
        }
    }

    pKhoiGach->iBoard += 1;
    return 1;
}

void SetValue(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1)
            {
                g_board[pKhoiGach->iBoard + i][pKhoiGach->jBoard + j] = 1;
            }
        }
    }
}

void RotateValue(khoi_gach_t * pKhoiGach)
{
    int i, j;
    int **tmpArr;
    int tmpRow = pKhoiGach->col;
    int tmpCol = pKhoiGach->row;
    tmpArr = (int**)malloc(tmpRow*sizeof(int *));
    for (i = 0; i < tmpRow; i++)
    {
        tmpArr[i] = (int*)malloc(tmpCol*sizeof(int));
    }

    for (i = pKhoiGach->row - 1; i >= 0; i--)
    {
        for (j = pKhoiGach->col - 1; j >= 0; j--)
        {
            tmpArr[j][pKhoiGach->row - i - 1] = pKhoiGach->arr[i][j];
        }
    }

    for (i = 0; i < tmpRow; i++)
    {
        for (j = 0; j < tmpCol; j++)
        {
            if (!Inside(pKhoiGach->iBoard + i, pKhoiGach->jBoard + j) || g_board[pKhoiGach->iBoard + i][pKhoiGach->jBoard + j] == 1)
            {
                return;
            }
        }
    }

    for (i = 0; i < pKhoiGach->row; i++)
    {
        free(pKhoiGach->arr[i]);
    }
    free(pKhoiGach->arr);

    pKhoiGach->col = tmpCol;
    pKhoiGach->row = tmpRow;
    pKhoiGach->arr = tmpArr;
}


void DrawKhoiGach(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1 && (pKhoiGach->iBoard +i) > 3)
            {
                SCR_SetTextColor(LIGHT_RED);
                SCR_GotoXY(LEFT + pKhoiGach->jBoard + j + 1, TOP + pKhoiGach->iBoard + i - 3);
                printf("%c", 2);
            }
        }
    }
}

void DeleteKhoiGach(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        for (int j = 0; j < pKhoiGach->col; j++)
        {
            if (pKhoiGach->arr[i][j] == 1 && (pKhoiGach->iBoard + i) > 3)
            {
                SCR_SetTextColor(BLACK);
                SCR_GotoXY(LEFT + pKhoiGach->jBoard + j + 1, TOP + pKhoiGach->iBoard + i - 3);
                printf(" ");
            }
        }
    }
}


void InitGame(info_t * info)
{
    info->level = 1;
    info->score = 0;
    info->speed = 0.4f;
}

int UpdateInfo(info_t * info, int score)
{
    info->score += score;
    if (info->score >= 200 && info->level < 2)
    {
        info->level++;
        info->speed -= 0.1f;
    }
    return 0;
}

void DrawPointTable(info_t info)
{
    SCR_SetTextColor(LIGHT_YELLOW);
    SCR_GotoXY(LEFT + MAX_COL + 2, 10);
    printf("SCORE: %3d", info.score);
    SCR_GotoXY(LEFT + MAX_COL + 2, 11);
    printf("LEVEL: %3d", info.level);
    SCR_GotoXY(LEFT + MAX_COL + 2, 12);
    printf("SPEED: %3f", info.speed);
}


int Check(khoi_gach_t * pKhoiGach, info_t * info)
{
    int i, j, count;
    i = pKhoiGach->row - 1;

    if (pKhoiGach->iBoard <= 3)
    {
        return -1; // Game over
    }
    if (info->score>=300)
    {
        return 0; // Win
    }
    do
    {
        count = 0;
        for (j = 0; j < MAX_COL; j++)
        {
            if (g_board[pKhoiGach->iBoard + i][j] == 1)
            {
                count++;
            }
        }

        if (count == MAX_COL)
        {
            UpdateInfo(info, 20);
            UpdateToaDo(pKhoiGach->iBoard + i);
            DisplayBoard();
        }
        else
        {
            i -= 1;
        }

    } while (i >= 0);

    return 1;
}


void HuyKhoiGach(khoi_gach_t * pKhoiGach)
{
    for (int i = 0; i < pKhoiGach->row; i++)
    {
        free(pKhoiGach->arr[i]);
    }
    free(pKhoiGach->arr);

    free(pKhoiGach);
    pKhoiGach = NULL;
}

int Loai(void)
{
    int x = rand() % 7;
    int loai = 0;
    switch (x)
    {
    case 0:
        loai = 15;
        break;
    case 1:
        loai = 31;
        break;
    case 2:
        loai = 51;
        break;
    case 3:
        loai = 30;
        break;
    case 4:
        loai = 58;
        break;
    case 5:
        loai = 57;
        break;
    case 6:
        loai = 60;
        break;
    default:
        /* Do nothing */
        break;
    }

    return loai;
}

void Ve_Next(int id)
{
    khoi_gach_t *pNext = CreateKhoiGach(id);
    int iRoot = LEFT + MAX_COL + 5;
    int jRoot = TOP;
    for (int i = 0; i < pNext->row; i++)
    {
        for (int j = 0; j < pNext->col; j++)
        {
            if (pNext->arr[i][j] == 1)
            {
                SCR_SetTextColor(LIGHT_GREEN);
                SCR_GotoXY(iRoot + j, jRoot + i);
                printf("%c", 2);
            }
        }
    }

    HuyKhoiGach(pNext);
}

void Xoa_Next(void)
{
    int iRoot = LEFT + MAX_COL + 5;
    int jRoot = TOP;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            SCR_SetTextColor(BLACK);
            SCR_GotoXY(iRoot + j, jRoot + i);
            printf(" ");
        }
    }
}
