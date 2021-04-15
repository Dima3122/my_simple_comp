#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>

enum colors
{
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    pink = 5,
    lightblue = 6, 
    white = 7,  
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (enum colors a);
int mt_setbgcolor (enum colors a);
