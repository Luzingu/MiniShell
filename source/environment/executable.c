#include "../../header/minishell.h"

char *my_getenv(char **env, char *name)
{
    int name_len = (int)ft_strlen(name);

    for (int i = 0; env[i] != NULL; i++) 
    {
        if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
        {
            return &env[i][name_len + 1];
        }
    }
    return (NULL);
}
