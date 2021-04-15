#include "graphic.h"

int mt_clrscr (void)
{
    printf("\E[H\E[J");
    return 0;
}

int mt_gotoXY (int x, int y)
{
    printf("\E[%d;%dH",y,x);
    return 0;
}

int mt_getscreensize (int * rows, int * cols)
{
    struct winsize ws;
    if (!ioctl(1, TIOCGWINSZ, &ws))
    {
        *rows = ws.ws_row, *cols = ws.ws_col;
    } 
    return 0;
}

int mt_setfgcolor (enum colors a)
{
    printf("\E[3%dm", a);
    return 0;
}

int mt_setbgcolor (enum colors a)
{
    printf("\E[4%dm", a);
    return 0;
}
