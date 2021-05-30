#include "alu_cu.h"
#include "foo.h"
int result_pred_operation;
void ALU(int command, int operand)
{
    if (command == 30) //Выполняет сложение слова в аккумуляторе и слова из указанной ячейки памяти (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        accumulator = accumulator+ value;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 31) //Вычитает из слова в аккумуляторе слово из указанной ячейки памяти (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        accumulator = accumulator - value;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 32) //Выполняет деление слова в аккумуляторе на слово из указанной ячейки памяти (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        if (value != 0)
        {
            accumulator = accumulator / value;
            result_pred_operation = accumulator;
            sc_regSet(ignore_clock_pulses, 0);
            sc_regSet(Invalid_command_specified, 0);
        }
        else
        {
            sc_regSet(Division_by_0_error, 1);
        }
    }
    else if (command == 33) //Вычисляет произведение слова в аккумуляторе на слово из указанной ячейки памяти (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        accumulator = accumulator * value;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 51) // Двоичная инверсия слова в аккумуляторе и занесение результата в указанную ячейку памяти
    {
        int value = accumulator;
        value = ~value;
        sc_memorySet(operand, value);
        result_pred_operation = value;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 52) //Логическая операция И между содержимым аккумулятора и словом по указанному адресу (результат в аккумуляторе)
    {
        int value = accumulator, elem;
        sc_memoryGet(operand, &elem);
        accumulator = value & elem;
        result_pred_operation = accumulator;
        sc_memorySet(operand, value);
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 53) //Логическая операция ИЛИ между содержимым аккумулятора и словом по указанному адресу (результат в аккумуляторе)
    {
        int value = accumulator, elem;
        sc_memoryGet(operand, &elem);
        accumulator = value || elem;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 54) //Логическая операция исключающее ИЛИ между содержимым аккумулятора и словом по указанному адресу (результат в аккумуляторе)
    {
        int value = accumulator, elem;
        sc_memoryGet(operand, &elem);
        accumulator = value ^ elem;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 60) //Логический двоичный сдвиг содержимого указанной ячейки памяти влево (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        accumulator = value << 1;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 61) // Логический двоичный сдвиг содержимого указанной ячейки памяти вправо (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        accumulator = value >> 1;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 62) //Циклический двоичный сдвиг содержимого указанной ячейки памяти влево (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        int part1 = value << 15;
        int part2 = value >> 1;
        accumulator = part1 || part2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 63) //Циклический двоичный сдвиг содержимого указанной ячейки памяти вправо (результат в аккумуляторе)
    {
        int value;
        sc_memoryGet(operand, &value);
        int part1 = value << 1;
        int part2 = value >> 15;
        accumulator = part1 || part2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 65) //Сложение содержимого указанной ячейки памяти с ячейкой памяти, адрес которой находится в аккумуляторе (результат в аккумуляторе)
    {
        int value1, value2;
        sc_memoryGet(operand, &value1);
        sc_memoryGet(accumulator, &value2);
        accumulator = value1 + value2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 66) //Вычитание из содержимого указанной ячейки памяти содержимого ячейки памяти, адрес которой
    {                       //находится в аккумуляторе (результат в аккумуляторе)
        int value1, value2;
        sc_memoryGet(operand, &value1);
        sc_memoryGet(accumulator, &value2);
        accumulator = value1 - value2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 67) // Логический двоичный сдвиг содержимого указанного участка памяти влево на количество
    {                       //разрядов, указанное в аккумуляторе (результат в аккумуляторе)
        
        int value;
        sc_memoryGet(operand, &value);
        accumulator = value << accumulator;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 68) //Логический двоичный сдвиг содержимого указанного участка памяти вправо на количество
    {                       //разрядов, указанное в аккумуляторе (результат в аккумуляторе)
        int value;
        sc_memoryGet(operand, &value);
        accumulator = value >> accumulator;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 69) //Циклический двоичный сдвиг содержимого указанного участка памяти влево на количество
    {                       //разрядов, указанное в аккумуляторе (результат в аккумуляторе)
        int value;
        sc_memoryGet(operand, &value);
        int part1 = value >> (16 - accumulator);
        int part2 = value << accumulator;
        accumulator = part1 || part2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 70) //Циклический двоичный сдвиг содержимого указанного участка памяти вправо на количество
    {                       //разрядов, указанное в аккумуляторе (результат в аккумуляторе)
        int value;
        sc_memoryGet(operand, &value);
        int part1 = value << (16 - accumulator);
        int part2 = value >> accumulator;
        accumulator = part1 || part2;
        result_pred_operation = accumulator;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 75) //Сложение содержимого указанной ячейки памяти с ячейкой памяти, адрес которой находится
    {                       //в ячейке памяти, указанной в аккумуляторе (результат в аккумуляторе)
        if (accumulator >= 0 || accumulator <= 99)
        {
            int value, value2;
            sc_memoryGet(accumulator, &value);
            sc_memoryGet(operand, &value2);
            accumulator = value + value2;
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 76) //Вычитание из содержимого указанной ячейки памяти содержимого
    {                       //ячейки памяти, адрес которой находится в ячейке памяти, указанной в аккумуляторе (результат в аккумуляторе)
        if (accumulator >= 0 || accumulator <= 99)
        {
            int value, value2;
            sc_memoryGet(accumulator, &value);
            sc_memoryGet(operand, &value2);
            accumulator = value - value2;
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else //иначе поднимаем флаги
    {
        sc_regSet(ignore_clock_pulses, 1);
        sc_regSet(Invalid_command_specified, 1);
    }
}

int CU()
{
    int command = 0, operand = 0;
    int value;
    sc_memoryGet(instruction_counter, &value);
    if (sc_commandDecode(value, &command, &operand))
    {
        sc_regSet(ignore_clock_pulses, 1);
        sc_regSet(Invalid_command_specified, 1);
    }
    else if (command == 10) //Ввод с терминала в указанную ячейку памяти с контролем переполнения
    {
        int value;
        rk_mytermregime(1, 0, 1, 0, 1);
        scanf("%x", &value);
        if (value > 65535)
        {
            value = 65535;
        }
        else if (value < 0)
        {
            value = 0;
        }
        rk_mytermrestore();
        sc_memorySet(operand, value);
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 11) //Вывод на терминал значения указанной ячейки памяти
    {
        int value;
        rk_mytermregime(1, 0, 1, 0, 1);
        sc_memoryGet(operand, &value);
        printf("Значение ячейки %d : %X\n", operand ,value);
        getchar();
        rk_mytermrestore();
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 20) //Загрузка в аккумулятор значения из указанного адреса памяти
    {
        sc_memoryGet(operand, &accumulator);
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 21) //Выгрузка значения из аккумулятора по указанному адресу памяти
    {
        sc_memorySet(operand, accumulator);
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 40) //Переход к указанному адресу памяти
    {
        if (operand < 0 || operand > 99)
        {
            return 0;
        }
        instruction_counter = operand;
        jump_memory(instruction_counter);
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 41) //Переход к указанному адресу памяти, если в аккумуляторе находится отрицательное число
    {
        if (accumulator < 0)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 42) // Переход к указанному адресу памяти, если в аккумуляторе находится нуль
    {
        if (accumulator == 0)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 43) //Останов, выполняется при завершении работы программы
    {
        printf("Работа программы завершается...\n");
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
        exit(0);
    }
    else if (command == 55) //Переход к указанному адресу памяти, если в аккумуляторе находится положительное число
    {
        if (accumulator > 0)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 56) // Переход к указанному адресу памяти, если при сложении произошло переполнение
    {
        int sum = arr[operand] + accumulator;
        if (sum > 65535)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 57) //Переход к указанному адресу памяти, если при сложении не произошло переполнение
    {
        int sum = arr[operand] + accumulator;
        if (sum <= 65535)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 58) //Переход к указанному адресу памяти, если результат предыдущей операции чѐтный
    {
        if (result_pred_operation %2 == 0)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 59) //Переход к указанному адресу памяти, если результат предыдущей операции нечѐтный
    {
        if (result_pred_operation %2 != 0)
        {
            if (operand < 0 || operand > 99)
            {
                return 0;
            }
            instruction_counter = operand;
            jump_memory(instruction_counter);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 64) // Получение дополнительного кода содержимого указанной ячейки памяти(результат в аккумуляторе)
    {
        accumulator = operand;
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 71) //Перемещение содержимого указанной ячейки памяти в ячейку, адрес которой указан в аккумуляторе
    {
        if (accumulator >= 0 || accumulator <= 99)
        {
            int value;
            sc_memoryGet(operand, &value);
            sc_memorySet(accumulator, value);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 72) //Перемещение содержимого ячейки памяти, адрес которой содержится в аккумуляторе, в указанную ячейку памяти
    {
        if (operand >= 0 || operand <= 99)
        {
            int value;
            sc_memoryGet(accumulator, &value);
            sc_memorySet(operand, value);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 73) //Перемещение содержимого указанной ячейки памяти в ячейку памяти, адрес которой находится в ячейке памяти,
    {                       // на которую указывает значение аккумулятора
        if (accumulator >= 0 || accumulator <= 99)
        {
            int value, address;
            sc_memoryGet(accumulator, &value);
            sc_commandDecode(value, &command, &address);
            sc_memoryGet(operand, &value);
            sc_memorySet(address, value);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else if (command == 74) //Перемещение в указанный участок памяти содержимого участка памяти, адрес которого находится в участке памяти, указанном в аккумуляторе
    {
        if (accumulator >= 0 || accumulator <= 99)
        {
            int value, address;
            sc_memoryGet(accumulator, &value);
            sc_commandDecode(value, &command, &address);
            sc_memoryGet(address, &value);
            sc_memorySet(operand, value);
        }
        sc_regSet(ignore_clock_pulses, 0);
        sc_regSet(Invalid_command_specified, 0);
    }
    else
    {
        ALU(command, operand);
    }
    return 0;
}