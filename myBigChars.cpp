#include "myBigChars.h"

int bc_printA (const char * str)
{
    int size = strlen(str);
    printf("\E(0");//включить рисование
    for (int i = 0; i < size; i++)
    {
        printf("%c", str[i]);
    }
    printf("\E(B");//выключить рисование
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{   
    mt_gotoXY(x1,y1);
    int size_x = x2-x1;
    int size_y = y2 - y1;
    printf("\E(0");
    printf(Angel_LU);
    for (int i = 0; i < size_x -1 ; i++)
    {
        printf(Line_xor);
    }
    printf(Angel_RU);
    for (int i = 0; i < size_y -1; i++)
    {
        mt_gotoXY(x2,y1 + i+1);
        printf(Line_ver);
    }
    mt_gotoXY(x1 + 1,y2);
    for (int i = size_x -1; i > 0; i--)
    {
        printf(Line_xor);
    }
    mt_gotoXY(x2,y2);
    printf(Angel_RD);
    mt_gotoXY(x1,y2);
    printf(Angel_LD);
    for (int i = 0; i < size_y -1; i++)
    {
        mt_gotoXY(x1,y1 + i+1);
        printf(Line_ver);
    }
    printf("\E(B");
    return 0;
}

int bc_printbigchar (long int num[2], int x, int y, enum colors a, enum colors b) 
{
    mt_gotoXY(x,y);
    int count = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((i%8) == 0)
        {
            count++;
            mt_gotoXY(x, y + count);
        }
        if ((num[1]>>i)&1)
        {
            bc_printA(CUBE);
        }
        else
        {
            printf(" ");
        }
    }
    for (int i = 0; i < 32; i++)
    {
        if ((i%8) == 0)
        {
            count++;
            mt_gotoXY(x, y + count);
        }
        if ((num[0]>>i)&1)
        {
            bc_printA(CUBE);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}

int bc_setbigcharpos(long int num[2], int x, int y, int value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) 
    {
        return 1;
    }
    int id = 1;
    if (y > 3) 
    {
        id = 0;
        y -= 4;
    }
    if (value == 1 || value == 0) 
    {
        if (value == 1) 
        {
            num[id] |= 1 << (x + y * 8);
        } 
        else 
        {
            num[id] &= ~(1 << (x + y * 8));
        }
        return 0;
    }
    return 1;
}

int bc_getbigcharpos(long int num[2], int x, int y, int *value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) 
    {
        return 1;
    }
    int id = 1;
    if (y > 3) 
    {
        id = 0;
        y -= 4;
    }
    *value = (num[id] >> (x + y * 8)) & 1;
    return 0;
}

int bc_bigcharwrite (long int num[2], char* filename)
{
    FILE* output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Ошибка открытия файла");
		return 1;
	}
	for (int i = 0; i < 2; ++i)
	{
		fprintf(output, "%ld ", num[i]);
	}
    fclose(output);
	return 0;
}

int bc_bigcharread (long int num[2], char* filename, int *counter)
{
    FILE* output = fopen(filename, "rb");
	if (output == NULL) 
	{
		printf("Ошибка открытия файла");
		return 1;
	}
    char str[5000];
	while (fgets(str,5000,output))
	{
		fprintf(stdout, "%s", str);
	}
	char buf[2] = " ";
	char* istr = NULL; 
	istr = strtok(str, buf);
	int count = 1;
	num[0] = atoi(istr);
	while (istr != NULL)
	{
		num[count] = atoi(istr);
		istr = strtok(NULL, buf);
		count++;
	}
    counter = &count;
	fclose(output);
    return 0;
}