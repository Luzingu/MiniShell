#include "../../header/minishell.h"


void bubble_sort(char **matrix, int n)
{
    int swapped;
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < n - 1)
    {
        swapped = 0;
        
        while (j < n - i - 1)
        {
            if (strncmp(matrix[j], matrix[j + 1], 100) > 0)
            {
                char *temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
                swapped = 1;
            }
            j++;
        }
        if (!swapped)
            break;
        i++;
    }
}

void ft_env(t_env *env)
{
    char **matrix;
    int nb_split;
    int i;

    i = 0;
    matrix = env_to_matrix(env);
    nb_split = numb_split(matrix);
    bubble_sort(matrix, nb_split);
    while (i < nb_split)
    {
        ft_putendl_fd(matrix[i], 1);
        i++;
    }
}

char *ft_getenv(t_env *env, char *var)
{
    t_env *env_tmp;

    env_tmp = env;
    while (env_tmp)
    {
        if (ft_strncmp(env_tmp->key, var, ft_strlen(var)) == 0)
            return (env_tmp->value);
        env_tmp = env_tmp->next;
    }
    return (NULL); 
}