#include "foo.h"

using namespace std;

CharVector *new_vector(int initial_capacity) //создает новый массив
{
    CharVector *z = new CharVector;
    if (z == NULL)
    {
        exit(-1);
    }
    z->ptr = new char[initial_capacity];
    if (z->ptr == NULL)
    {
        exit(-1);
    }
    z->capacity = initial_capacity;
    z->size = 0;
    return z;
}

int program_load(CharVector *z, FILE *text, char **a)
{
    fread(z->ptr, 1, z->capacity, text);
    fseek(text, 0, SEEK_SET);
    char sep[15] = "\n";
    char *t;
    int i = 0;

    t = strtok(z->ptr, sep);
    while (t != NULL)
    {
        a[i] = t;
        t = strtok(NULL, sep);
        i++;
    }
    return i;
}

int count_str(CharVector *z)
{
    int count = 0;
    char sep[15] = "\n";
    for (int i = 0; i < z->size; i++)
    {
        if (z->ptr[i] == sep[1])
        {
            count++;
        }
    }
    count++;
    return count;
}

int get_operation_and_value(char *a, char *command, int *value, int *cell) //какая операция выполняется
{
    char *text = a;
    char *t;
    char sep[15] = " \0";
    char **arr = new char *[10];
    for (int i = 0; i < 50; i++)
    {
        arr[i] = new char(100);
    }
    int size = strlen(command);
    for (int i = 0; i < size; i++)
    {
        command[i] = sep[1];
    }
    int i = 0;
    t = strtok(text, sep);
    while (t != NULL)
    {
        arr[i] = t;
        t = strtok(NULL, sep);
        i++;
    }
    size = strlen(arr[1]);
    for (int i = 0; i < size; i++)
    {
        command[i] = arr[1][i];
    }
    size = 0;
    *value = atoi(arr[2]);
    *cell = atoi(arr[0]);
    return i;
}

void execute_command_simple_accembler(FILE *answer, char *command, int operand, int cell)
{
    int b = 0;
    if (!strcmp(command, "READ")) //запись в ячейку
    {
        sc_commandEncode(10, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "LOAD"))
    {
        sc_commandEncode(20, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "SUB"))
    {
        sc_commandEncode(31, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "JNEG"))
    {

        sc_commandEncode(41, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "WRITE"))
    {
        sc_commandEncode(11, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "HALT"))
    {
        sc_commandEncode(43, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "="))
    {
        sc_commandEncode(10, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "+"))
    {
        sc_commandEncode(30, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "-"))
    {
        sc_commandEncode(31, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "/"))
    {
        sc_commandEncode(32, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "*"))
    {
        sc_commandEncode(33, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "DELOAD"))
    {
        sc_commandEncode(21, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "EVEN"))
    {
        sc_commandEncode(58, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "ODD"))
    {
        sc_commandEncode(59, operand, &b);
        sc_memorySet(cell, b);
    }
    else if (!strcmp(command, "ZERO"))
    {
        sc_commandEncode(42, operand, &b);
        sc_memorySet(cell, b);
    }
}

void check_open(FILE *a)
{
    if (a == NULL)
    {
        printf("Произошла ошибка открытия текстого файла. Завершение программы.\n");
        exit(1);
    }
}

void start_compiling_simple_accembler(char *filename1, char *filename2)
{
    int size = 0, value = 0, cell = 0;
    FILE *text;
    FILE *answer;
    text = fopen(filename1, "r");
    answer = fopen(filename2, "w");
    check_open(text);
    check_open(answer);

    fseek(text, 0, SEEK_END);
    size = ftell(text);
    fseek(text, 0, SEEK_SET);
    CharVector *z = new_vector(size);

    z->size = fread(z->ptr, 1, z->capacity, text);
    char *command = new char(z->size);
    char **a = new char *[z->size];
    for (int i = 0; i < 50; i++)
    {
        a[i] = new char[100];
    }
    int g = program_load(z, text, a);
    g = count_str(z);
    for (int i = 0; i < g; i++)
    {
        get_operation_and_value(a[i], command, &value, &cell);
        execute_command_simple_accembler(answer, command, value, cell);    
    }
    sc_memorySave(filename2);
    cout << "Компиляция программы завершена!" << endl;
}