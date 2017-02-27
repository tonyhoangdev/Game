#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include "Screen.h"

#define MAX_ROW 22
#define MAX_COL 10
#define LEFT 4
#define TOP  4

extern int g_board[MAX_ROW][MAX_COL];

typedef struct
{
    int **arr;
    int row, col;
    int iBoard, jBoard;
} khoi_gach_t;

void DrawBoard(void);
void DisplayBoard(void);
void UpdateToaDo(int row);
khoi_gach_t * CreateKhoiGach(int id);

int Inside(int x, int y);
int Left(int x, int y);
int Right(int x, int y);
int Down(int x, int y);

void MoveLeft(khoi_gach_t * pKhoiGach);
void MoveRight(khoi_gach_t * pKhoiGach);
int MoveDown(khoi_gach_t * pKhoiGach);

void SetValue(khoi_gach_t * pKhoiGach);
void RotateValue(khoi_gach_t * pKhoiGach);

void DrawKhoiGach(khoi_gach_t * pKhoiGach);
void DeleteKhoiGach(khoi_gach_t * pKhoiGach);

typedef struct
{
    int score;
    int level;
    float speed;
} info_t;

void InitGame(info_t * info);
int UpdateInfo(info_t * info, int score);
void DrawPointTable(info_t info);

int Check(khoi_gach_t * pKhoiGach, info_t * info);

void HuyKhoiGach(khoi_gach_t * pKhoiGach);

int Loai(void);

void Ve_Next(int id);
void Xoa_Next(void);

#endif /* TETRIS_H */
