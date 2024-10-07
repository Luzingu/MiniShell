#include "../header/minishell.h"

void str_dup_env(char **env, t_mini *mini)
{
    t_env *new;
    char **my_env;
    int i;

    i = 0;
    new = NULL;
    while (env[i])
    {
        my_env = ft_split(env[i], '=');
        if(!new)
        {
            new = add_envirenoment(my_env[0], my_env[1]);
            mini->env = new;
            mini->env_copy = new;
        }
        else
        {
            new->next = add_envirenoment(my_env[0], my_env[1]);
            new = new->next;
        }
        i++;
    }
}
