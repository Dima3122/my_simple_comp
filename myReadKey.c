#include "myReadKey.h"

static struct termios stored;


// tcflag_t c_iflag;       режимы ввода
// tcflag_t c_oflag;       режимы вывода
// tcflag_t c_cflag;       режимы управления
// tcflag_t c_lflag;       режимы локали
// cc_t c_cc[NCCS];        управляющие символы

int rk_readkey(enum keys *a) //cчетчик клавиш
{
    rk_mytermregime(1, 0, 1, 1, 1);
    char buf[8];
    read(STDIN_FILENO, buf, 8); //STDDIN_FILENO уровень ядра
    if (!strcmp(buf, "\033[A"))
    {
        *a = key_up;
    }
    else if (!strcmp(buf, "\033[B"))
    {
        *a = key_down;
    }
    else if (!strcmp(buf, "\033[C"))
    {
        *a = key_right;
    }
    else if (!strcmp(buf, "\033[D"))
    {
        *a = key_left;
    }
    else if (!strcmp(buf, "\033[15~"))
    {
        *a = f5;
    }
    else if (!strcmp(buf, "\033[17~"))
    {
        *a = f6;
    }
    else if (buf[0] == '\n')
    {
        *a = enter;
    }
    else if (buf[0] == 'l')
    {
        *a = load;
    }
    else if (buf[0] == 's')
    {
        *a = save;
    }
    else if (buf[0] == 'r')
    {
        *a = run;
    }
    else if (buf[0] == 't')
    {
        *a = step;
    }
    else if (buf[0] == 'i')
    {
        *a = i;
    }
    else if ((int)buf[0] == 27)
    {
        *a = Exit;
    }
    else if (buf[0] == 'a')
    {
        *a = Signal;
    }
    else
    {
        *a = key_other;
    }
    rk_mytermrestore();
    return 0;
}

int rk_mytermsave(void) //сохранить терминал
{
    if (!tcgetattr(0, &stored))
    {
        return 1;
    }
    return 0;
}

int rk_mytermrestore(void) //загрузить терминал
{
    if (!tcsetattr(0, TCSANOW, &stored))
    {
        return 1;
    }
    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) //режим терминала
{
    struct termios new_settings = stored;
    rk_mytermsave();
    if (regime == 1)
    {
        new_settings.c_lflag &= (~ICANON);
        if (sigint == 1)//включение и отключение флагов. Поднимаем флаги при помощи битовых операций
        {
            new_settings.c_lflag &= (~ISIG);
        }
        else
        {
            new_settings.c_lflag |= ISIG;
        }
        if (echo == 1)//включение эхо
        {
            new_settings.c_lflag &= (~ECHO);
        }
        else
        {
            new_settings.c_lflag |= ECHO;
        }
        new_settings.c_cc[VMIN] = vmin;
        new_settings.c_cc[VTIME] = vtime;
    }
    else
    {
        new_settings.c_lflag |= ICANON;
    }
    tcsetattr(0, TCSANOW, &new_settings);
    return 0;
}