#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
    load = 1,
    save = 2,
    run = 3,
    step = 4,
    Exit = 6,
    Signal = 7,
    t = 8,
    i = 9,
    f5 = 10,
    f6 = 11,
    key_down = 12,
    key_up = 13,
    key_left = 14,
    key_right = 15,
    key_other = 16,
    enter = 17,
};

int rk_readkey(enum keys *a);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);