#include "graphic.h"

#define Angel_LU "l"
#define Angel_LD "m"
#define Angel_RU "k"
#define Angel_RD "j"
#define Line_ver "x"
#define Line_xor "q"
#define CUBE "a"

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar (long int num[2], int x, int y, enum colors a, enum colors b); 
int bc_setbigcharpos (long int num[2], int x, int y, int value);
int bc_getbigcharpos(long int num[2], int x, int y, int *value);
int bc_bigcharwrite (long int num[2], char* filename);
int bc_bigcharread (long int num[2], char* filename, int *counter);