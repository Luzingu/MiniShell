#include "../header/minishell.h"

int numb_split (char **matrix)
{
    int num;

    num = 0;
    while (matrix[num])
        num++;
    return (num);
}
