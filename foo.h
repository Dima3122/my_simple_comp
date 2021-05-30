#pragma once
#include "myBigChars.h"
#include "myReadKey.h"
#include "memory.h"
#include "alu_cu.h"
#include "simple_and_basic_accembler.h"
#include <sys/time.h>
#include <math.h>

extern struct itimerval nval, oval;//обьявляем таймер
extern int instruction_counter;
extern int accumulator;
extern int IGNOR_SYS_TIME;
struct position_cors
{
    int x;
    int y;
};
extern struct position_cors cr;
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
void f5(enum keys a);
void f6(enum keys a);
void Run(enum keys a);
void instruction_count();
void jump_memory(int instruction_counter);
void print_input_outpoot();
void next_command(enum keys a);
void Save(enum keys a);
void compiling_the_program(enum keys a);
void Load(enum keys a);