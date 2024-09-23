#include "../../header/minishell.h"



char *my_getenv(char **env, const char *name)
{
    size_t name_len = ft_strlen(name);

    for (int i = 0; env[i] != NULL; i++) 
    {
        // Verifica se a variável começa com o nome e é seguida de '='
        if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
        {
            return &env[i][name_len + 1];
        }
    }
    return NULL;
}

char *find_executable(char *cmd, char **env)
{
    struct stat buffer;

    if (stat(cmd, &buffer) == 0)
    {
        return strdup(cmd);
    }

    char *path_env = my_getenv(env, "PATH");
    if (!path_env)
        return (NULL);

    char **path_dirs = ft_split(path_env, ':');
    for (int i = 0; path_dirs[i]; i++)
    {
        char *full_path = ft_strjoin(ft_strjoin(path_dirs[i], "/"), cmd);
        if (full_path && stat(full_path, &buffer) == 0)
        {
            ft_free_mtrs(path_dirs);
            return full_path;
        }
        free(full_path);
    }
    ft_free_mtrs(path_dirs);
    return NULL;
}