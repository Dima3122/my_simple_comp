#include "foo.h"
#include <signal.h>
enum keys key = key_other;

int main()
{
    cr.x = 0;
    cr.y = 0;
    nval.it_interval.tv_sec = 3;
    nval.it_interval.tv_usec = 500;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    accumulator = 0;
    instruction_counter = 0;
    IGNOR_SYS_TIME = 1;
    signal(SIGALRM, timer);
    signal(SIGUSR1, sighandler);
    if (IGNOR_SYS_TIME == 0)
    {
        setitimer (ITIMER_REAL, &nval, &oval);
    }
    sc_memoryInit();
    sc_regInit();
    while (key != Exit)
    {
        drow();
        rk_readkey(&key);
        cursor(key);
        compiling_the_program(key);
        f5(key);
        f6(key);
        Run(key);
        next_command(key);
        Save(key);
        Load(key);
        if (key == i)
        {
            raise(SIGUSR1); 
        }
    }
    mt_gotoXY(1, 30);
    alarm(0);
    return 0;
}