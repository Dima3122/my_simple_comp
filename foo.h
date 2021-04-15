#include "myBigChars.h"
#include "myReadKey.h"
#include "memory.h"
#include <signal.h>
#include <sys/time.h>

#define IGNOR_SYS_TIME 0
struct itimerval nval, oval;//обьявляем таймер
int instruction_counter;
int accumulator;
struct position_cors
{
    int x;
    int y;
};
struct position_cors cr;
void print_mem();
void print_acc();
void print_instructioncounter();
void print_operation();
void print_flags();
void print_bigChars();
void print_Char(int value, int a, int b);
void print_keys();
void drow();
void cursor(enum keys a);
void restore_simple_computer();
void sighandler(int signo);
void signalhandler(int signo);
void timer(int signo);