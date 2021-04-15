#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define set_0 flag & (~(1 << (k--)))
#define set_1 flag | (1 << (k--))
#define overflow_during_operations 1 //переполнение во время операций
#define Division_by_0_error 2 //Деление на 0 ошибок
#define Out_of_bounds_error 3 //Ошибка за пределами границ
#define ignore_clock_pulses 4 //игнорировать тактовые импульсы
#define Invalid_command_specified 5 //Указана неверная команда

int* arr;
int flag;
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int register, int value);
int sc_regGet(int register, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
void printarray();