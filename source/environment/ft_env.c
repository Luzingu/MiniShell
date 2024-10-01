#include "../../header/minishell.h"

void ft_env(char **env, t_mini *mini)
{
    int i = -1;
    while (env[++i])
        ft_putendl_fd(env[i], 1);
    mini->last_return = 0;
}

char *ft_getenv(char **env, char *var)
{
    int i = -1;
    int len_var;
    
    len_var = ft_strlen(var);
    while (env[++i])
    {
        if (ft_strncmp(env[i], var, len_var) == 0 && env[i][len_var] == '=')
            return (env[i] + len_var + 1);
    }
    return (NULL);
}