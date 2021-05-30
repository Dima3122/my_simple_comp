#include <iostream>
#include <stddef.h>
#include <map>
struct CharVector
{
    char *ptr; //указатель
    int size; //количество заполненных элементов счетчик
    int capacity; //вместимость счетчик
};

extern int count_perem;

CharVector* new_vector(size_t initial_capacity);
int program_load(CharVector *z, FILE *text, char** a);
int count_str(CharVector* z);
int get_operation_and_value(char* a, char* command, int* value, int* cell);
void execute_command_simple_accembler(FILE* answer, char* command, int operand, int cell);
void execute_command_simple_basic(FILE* answer, char* a);
void check_open(FILE *a);
void start_compiling_simple_accembler(char* filename1, char* filename2);
void get_operation(char* a, char* command);
void get_value(char *a, char *value);