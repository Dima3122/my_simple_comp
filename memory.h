#pragma once
#define set_0 flag & (~(1 << (k--)))
#define set_1 flag | (1 << (k--))
#define overflow_during_operations 0 //переполнение во время операций
#define Division_by_0_error 1 //Деление на 0 ошибок
#define Out_of_bounds_error 2 //Ошибка за пределами границ
#define ignore_clock_pulses 3 //игнорировать тактовые импульсы
#define Invalid_command_specified 4 //Указана неверная команда

extern int* arr;
extern int flag;

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