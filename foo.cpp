#include "foo.h"
int instruction_counter;
int accumulator;
int IGNOR_SYS_TIME;
struct itimerval nval, oval;
struct position_cors cr;

long int zero[2] = {0b11111111110000111100001111000011, 0b11000011110000111100001111111111};
long int one[2] = {0b11111111000110000001100000011000, 0b00011000000111100001110000011000};
long int two[2] = {0b11111111000001100000110000011000, 0b00110000011000001100001101111110};
long int three[2] = {0b01111110110000110110000000110000, 0b00110000011000001100001101111110};
long int four[2] = {0b01100000011000001111111101100011, 0b01100110011011000111100001110000};
long int five[2] = {0b011111111110000001100000011000000, 0b11111111000000110000001111111111};
long int six[2] = {0b11111111110000111100001111000011, 0b11111111000000110000001111111111};
long int seven[2] = {0b00000011000001100000110000011000, 0b00110000011000001100000011111111};
long int eight[2] = {0b11111111110000111100001111000011, 0b11111111110000111100001111111111};
long int nine[2] = {0b11111111110000001100000011111111, 0b11000011110000111100001111111111};
long int plus[2] = {0b00011000000110000001100011111111, 0b11111111000110000001100000011000};
long int minus[2] = {0b00000000000000000000000011111111, 0b11111111000000000000000000000000};
long int A[2] = {0b01000010010000100100001001111110, 0b01000010010000100010010000011000};
long int B[2] = {0b00111110010000100100001001000010, 0b00111110010000100100001000111110};
long int C[2] = {0b01111110000000100000001000000010, 0b00000010000000100000001001111110};
long int D[2] = {0b00111110010000100100001001000010, 0b01000010010000100100001000111110};
long int E[2] = {0b01111110000000100000001000000010, 0b01111110000000100000001001111110};
long int F[2] = {0b00000010000000100000001000000010, 0b00111110000000100000001001111110};

void print_mem()
{
    bc_box(2, 1, 63, 12);
    mt_gotoXY(25, 1);
    printf("Memory");
    mt_gotoXY(3, 2);
    int value;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (cr.x == i && cr.y == j)
            {
                value = abs(arr[i * 10 + j]);
                printf("/%04X ", value);
            }
            else
            {
                if (arr[i * 10 + j] >= 0)
                {
                    printf("+%04X ", arr[i * 10 + j]);
                }
                else
                {
                    value = abs(arr[i * 10 + j]);
                    printf("-%04X ", value);
                }
            }
        }
        mt_gotoXY(3, i + 3);
    }
}

void print_acc()
{
    bc_box(64, 1, 83, 3);
    mt_gotoXY(69, 1);
    printf("Accumulator");
    mt_gotoXY(71, 2);
    if (accumulator >= 0)
    {
        printf("+%04x", accumulator);
    }
    else
    {
        printf("-%04x", abs(accumulator));
    }
}

void print_instructioncounter()
{
    bc_box(64, 4, 83, 6);
    mt_gotoXY(65, 4);
    printf("instructioncounter");
    mt_gotoXY(71, 5);
    printf("+%04d", instruction_counter);
}

void print_operation()
{
    bc_box(64, 7, 83, 9);
    mt_gotoXY(70, 7);
    printf("Operation");
    mt_gotoXY(71, 8);
    printf("+00 : 00");
}

void print_flags()
{
    int value = 0;
    bc_box(64, 10, 83, 12);
    mt_gotoXY(71, 10);
    printf("flags");
    mt_gotoXY(71, 11);
    sc_regGet(overflow_during_operations, &value);
    if (value == 1)
    {
        mt_gotoXY(69, 11);
        printf("П");
    }
    sc_regGet(Division_by_0_error, &value);
    if (value == 1)
    {
        mt_gotoXY(71, 11);
        printf("0");
    }
    sc_regGet(Out_of_bounds_error, &value);
    if (value == 1)
    {
        mt_gotoXY(73, 11);
        printf("М");
    }
    sc_regGet(ignore_clock_pulses, &value);
    if (value == 1)
    {
        mt_gotoXY(75, 11);
        printf("Т");
    }
    sc_regGet(Invalid_command_specified, &value);
    if (value == 1)
    {
        mt_gotoXY(77, 11);
        printf("Е");
    }
}

void print_bigChars()
{
    int value;
    int arr[4] = {0};
    bc_box(2, 13, 48, 22);
    sc_memoryGet(cr.x * 10 + cr.y, &value);
    value = abs(value);
    int cnt = 0;
    while (value)
    {
        int curr = value % 16;
        value /= 16;
        arr[cnt] = curr;
        ++cnt;
    }
    sc_memoryGet(cr.x * 10 + cr.y, &value);
    if (value >= 0)
    {
        bc_printbigchar(plus, 3, 13, black, black);
    }
    else
    {
        bc_printbigchar(minus, 3, 13, black, black);
    }
    print_Char(arr[3], 12, 13);
    print_Char(arr[2], 21, 13);
    print_Char(arr[1], 30, 13);
    print_Char(arr[0], 39, 13);
}

void print_Char(int value, int a, int b)
{
    switch (value)
    {
    case 0:
        bc_printbigchar(zero, a, b, black, black);
        break;
    case 1:
        bc_printbigchar(one, a, b, black, black);
        break;
    case 2:
        bc_printbigchar(two, a, b, black, black);
        break;
    case 3:
        bc_printbigchar(three, a, b, black, black);
        break;
    case 4:
        bc_printbigchar(four, a, b, black, black);
        break;
    case 5:
        bc_printbigchar(five, a, b, black, black);
        break;
    case 6:
        bc_printbigchar(six, a, b, black, black);
        break;
    case 7:
        bc_printbigchar(seven, a, b, black, black);
        break;
    case 8:
        bc_printbigchar(eight, a, b, black, black);
        break;
    case 9:
        bc_printbigchar(nine, a, b, black, black);
        break;
    case 10:
        bc_printbigchar(A, a, b, black, black);
        break;
    case 11:
        bc_printbigchar(B, a, b, black, black);
        break;
    case 12:
        bc_printbigchar(C, a, b, black, black);
        break;
    case 13:
        bc_printbigchar(D, a, b, black, black);
        break;
    case 14:
        bc_printbigchar(E, a, b, black, black);
        break;
    case 15:
        bc_printbigchar(F, a, b, black, black);
        break;
    default:
        break;
    }
}

void print_keys()
{
    bc_box(49, 13, 83, 22);
    mt_gotoXY(52, 13);
    printf("keys");
    mt_gotoXY(50, 14);
    printf("l - load");
    mt_gotoXY(50, 15);
    printf("s - save");
    mt_gotoXY(50, 16);
    printf("r - run");
    mt_gotoXY(50, 17);
    printf("t - step");
    mt_gotoXY(50, 18);
    printf("i - reset");
    mt_gotoXY(50, 19);
    printf("Z - accumulator");
    mt_gotoXY(50, 20);
    printf("X - instructioncounter");
    mt_gotoXY(50, 21);
    printf("C - compiling the program");
}

void print_input_outpoot()
{
    mt_gotoXY(1, 23);
    printf("Input/Outpoot:\n");
}

void drow()
{
    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == 0)
    {
        if (rows >= 26 && cols >= 84)
        {
            mt_clrscr();
            jump_memory(instruction_counter);
            print_mem();
            print_acc();
            print_instructioncounter();
            print_operation();
            print_flags();
            print_keys();
            print_bigChars();
            print_input_outpoot();
            mt_gotoXY(1, 24);
        }
        else
        {
            mt_gotoXY(abs(rows / 2) + 1, abs(cols / 2) - 15);
            printf("Make the terminal window bigger.");
            mt_gotoXY(1, 1);
            exit(-1);
        }
    }
}

void cursor(enum keys a)
{
    if (a == key_up)
    {
        if (cr.x == 0)
        {
            cr.x = 0;
        }
        else
        {
            cr.x--;
        }
    }
    else if (a == key_down)
    {
        if (cr.x == 9)
        {
            cr.x = 9;
        }
        else
        {
            cr.x++;
        }
    }
    else if (a == key_right)
    {
        if (cr.y == 9)
        {
            cr.y = 9;
        }
        else
        {
            cr.y++;
        }
    }
    else if (a == key_left)
    {
        if (cr.y == 0)
        {
            cr.y = 0;
        }
        else
        {
            cr.y--;
        }
    }
    else if (a == enter)
    {
        int value;
        rk_mytermregime(1, 0, 1, 0, 1);
        scanf("%x", &value);
        if (value > 65535)
        {
            value = 65535;
        }
        else if (value < -65535)
        {
            value = 0;
        }
        rk_mytermrestore();
        sc_memorySet(cr.x * 10 + cr.y, value);
    }
    instruction_count();
}

void instruction_count()
{
    instruction_counter = cr.x * 10 + cr.y;
}

void restore_simple_computer()
{
    instruction_counter = 0;
    accumulator = 0;
    for (int i = 0; i < 100; i++)
    {
        sc_memorySet(i, 0);
    }
    cr.x = 0;
    cr.y = 0;
    setitimer(ITIMER_REAL, &nval, &oval);
}

void compiling_the_program(enum keys a)
{
    if (a == c)
    {
        printf("погнали компилировать!!!!\n");
        char* filename1 = new char(100);
        char* filename2 = new char(100);
        char* command = new char(100); 
        scanf("%s %s %s", command, filename1, filename2);
        if (!strcmp(command, "sat"))
        {
            start_compiling_simple_accembler(filename1, filename2);
        }
        else
        {
            printf("Некоректная команда!");
        }
        getchar(); getchar();
    }
    
}

void sighandler(int signo)
{
    restore_simple_computer();
}

void timer(int signo)
{
    if (instruction_counter < 100)
    {
        CU();
        instruction_counter++;
    }
    if (instruction_counter > 99)
    {
        instruction_counter = 0;
    }
    drow();
}

void f5(enum keys a)
{
    if (a == z)
    {
        sc_memoryGet(cr.x * 10 + cr.y, &accumulator);
    }
}

void f6(enum keys a)
{
    if (a == x)
    {
        int value;
        rk_mytermregime(1, 0, 1, 0, 1);
        scanf("%d", &value);
        if (value < 0 || value > 99)
        {
            value = 0;
        }
        instruction_counter = value;
        rk_mytermrestore();
        jump_memory(instruction_counter);
    }
}

void jump_memory(int instruction_counter)
{
    cr.x = instruction_counter / 10;
    cr.y = instruction_counter % 10;
}

void Run(enum keys a)
{
    if (a == run && IGNOR_SYS_TIME == 1)
    {
        IGNOR_SYS_TIME = 0;
        setitimer(ITIMER_REAL, &nval, &oval);
        rk_mytermrestore();
    }
    else if (a == run && IGNOR_SYS_TIME == 0)
    {
        IGNOR_SYS_TIME = 1;
        alarm(0);
        rk_mytermrestore();
    }
}

void next_command(enum keys a)
{
    if (a == step)
    {
        if (instruction_counter < 100)
        {
            CU();
            instruction_counter++;
        }
        if (instruction_counter > 99)
        {
            instruction_counter = 0;
        }
    }
}

void Save(enum keys a)
{
    if (a == save)
    {
        char *a = new char(50);
        std::cout << "Введите название файла, куда сохранить:";
        std::cin >> a ;
        sc_memorySave(a);
        getchar();
    }
}

void Load(enum keys a)
{
    if (a == load)
    {
        char *a = new char(50);
        std::cout << "Введите название файла, откуда загрузить:";
        std::cin.getline(a,50);
        sc_memoryLoad(a);
        getchar();
    }
}