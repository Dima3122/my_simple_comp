#pragma once
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
    z = 10,
    x = 11,
    key_down = 12,
    key_up = 13,
    key_left = 14,
    key_right = 15,
    key_other = 16,
    enter = 17,
    c = 18,
};

int rk_readkey(enum keys *a);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);