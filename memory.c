#include "memory.h"

int sc_memoryInit()
{
	arr = (int*)malloc(131 * sizeof(int));
	if (arr == NULL)
	{
		return 1;
	}
	for (size_t i = 0; i < 131; i++)
	{
		arr[i] = 0;
	}
	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address > -1 && address < 131)
	{
		arr[address] = value;
	}
	else
	{
		sc_regSet(Out_of_bounds_error, 1);
		return Out_of_bounds_error;
	}
	return 0;
}

int sc_memoryGet(int address, int* value)
{
	if (address > -1 && address < 131)
	{
		*value = arr[address];
	}
	else
	{
		sc_regSet(Out_of_bounds_error, 1);
		return Out_of_bounds_error;
	}
	return 0;
}

int sc_memorySave(char* filename)
{
	FILE* output = fopen(filename, "wb");
	if (output == NULL)
	{
		printf("Ошибка открытия файла");
		return 1;
	}
	for (int i = 0; i < 100; ++i)
	{
		fprintf(output, "%d ", arr[i]);
	}
	fclose(output);
	return 0;
}

int sc_memoryLoad(char* filename)
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
	arr[0] = atoi(istr);
	while (istr != NULL)
	{
		arr[count] = atoi(istr);
		istr = strtok(NULL, buf);
		count++;
	}
	fclose(output);
	return 0;
}

int sc_regInit(void)
{
	flag = 0;
	return 0;
}

int sc_regSet(int k, int value)
{
	if (value == 1)
	{
		flag = set_1;
	}
	else
	{
		flag = set_0;
	}
	return 0;
}

int sc_regGet(int k, int* value)
{
	if (k < 0)
	{
		return -1;
	}
	return (flag >> (*value--)) & 0x1;
}

int sc_commandEncode(int command, int operand, int* value)
{
	if ((operand >= 0 ||operand <= 127) && (command >= 0 || command <= 127))
	{
		if (command != 10 || command != 11 || command != 20 || command != 21 || (command <= 30 && command >= 33) || 
		command != 40 || command != 41 || command != 42 || command != 43 || (command >= 51 && command <= 76))
		{
			sc_regSet(Invalid_command_specified, 1);
			return Invalid_command_specified;
		} 
		*value = (command << 7) | operand | 0x8000;
	}
	return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
	if ((value & 0x8000) == 0)//Узнаем команда ли это
	{	
	 	return -1;
	}
	int operanad2 = value & 0x7F;
	int command2 = (value >> 7) & 0x7F;
	if (command2 != 10 || command2 != 11 || command2 != 20 || command2 != 21 || (command2 <= 30 && command2 >= 33) || 
	command2 != 40 || command2 != 41 || command2 != 42 || command2 != 43 || (command2 >= 51 && command2 <= 76))
	{
		return Invalid_command_specified;
	}
	*command = command2;
	*operand = operanad2;
	sc_regSet(Invalid_command_specified, 1);
	return 0;
}

void printarray()
{
	for (size_t i = 0; i < 100; i++)
	{
		printf("arr(%ld) = %d\n", i, arr[i]);
	}
}