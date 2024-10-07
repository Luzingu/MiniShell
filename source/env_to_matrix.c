#include "../header/minishell.h"

char **env_to_matrix(t_env *env)
{
    t_env *env_tmp;
    char **matrix;
    char *tmp;
    int i;

    env_tmp = env;
    i = 0;
    while (env_tmp)
    {
        i++;
        env_tmp = env_tmp->next;
    }
    matrix = (char **)malloc(sizeof(char *) * (i + 1));
    env_tmp = env;
    i = 0;
    while (env_tmp)
    {
        tmp = ft_strdup(env_tmp->key);
        tmp = ft_strjoin(tmp, "=");
        tmp = ft_strjoin(tmp, env_tmp->value);
        if (tmp)
        {
            matrix[i] = tmp;
            i++;
        }
        env_tmp = env_tmp->next;
    }
    matrix[i] = NULL;
    return (matrix);
}
