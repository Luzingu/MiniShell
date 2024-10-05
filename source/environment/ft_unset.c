#include "../../header/minishell.h"

void ft_unset(char *args, t_env **env)
{
    t_env *env_tmp;
    t_env *prev;

    env_tmp = *env;
    prev = NULL;
    while (env_tmp)
    {
        if (ft_strncmp(env_tmp->key, args, ft_strlen(args)) == 0)
        {
            if (!prev)
                *env = env_tmp->next;
            else
                prev->next = env_tmp->next;
            free(env_tmp->key);
            free(env_tmp->value);
            free(env_tmp);
            break;
        }
        prev = env_tmp;
        env_tmp = env_tmp->next;
    }
}

int handle_unset(char **tmp, t_env **env)
{
    int n;

    n = 1;
    while (tmp[n])
    {
        ft_unset(tmp[n], env);
        n++;
    }
    return (0);
}