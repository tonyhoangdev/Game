#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>
#include <stdbool.h>

/** Defines **/
typedef enum
{
    BLACK = 0U,
    BLUE = 1U,
    GREEN = 2U,
    AQUA = 3U,
    RED = 4U,
    PURPLE = 5U,
    YELLOW = 6U,
    WHITE = 7U,
    GRAY = 8U,
    LIGHT_BLUE = 9U,
    LIGHT_GREEN = 10U,
    LIGHT_AQUA = 11U,
    LIGHT_RED = 12U,
    LIGHT_PURPLE = 13U,
    LIGHT_YELLOW = 14U,
    LIGHT_WHITE = 15U
} color_t;

void SCR_GotoXY(short x, short y);
void SCR_Clrscr(void);
void SCR_SetTextColor(color_t color);
void SCR_SetBGColor(color_t color);
void SCR_Delay(int ms);
void SCR_NoCursorType();

#endif /* SCREEN_H */
