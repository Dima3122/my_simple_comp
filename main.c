#include "foo.h"

enum keys key = key_other;

int main()
{
    cr.x = 2;
    cr.y = 1;
    nval.it_interval.tv_sec = 3;
    nval.it_interval.tv_usec = 500;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
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
        if (IGNOR_SYS_TIME == 0)
        {
            rk_readkey(&key);
            cursor(key);
        }    
        if (key == i)
        {
            raise(SIGUSR1); 
        }
    }
    return 0;
}