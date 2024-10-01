#include "../header/minishell.h"


int increment_shell_level(char **env)
{
    char *str_shell_level;    
    int shell_level;

    str_shell_level = ft_getenv(env, "SHLVL");
    if (!str_shell_level)
        return (1);
    else
    {
        shell_level = ft_atoi(str_shell_level);
        shell_level++;
    }
    return (shell_level);
}