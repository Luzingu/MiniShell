#include "../../header/minishell.h"

char *ft_get_pwd()
{
    char *cwd = malloc(PATH_MAX);
    if (cwd == NULL)
    {
        perror("malloc failed");
        return NULL; 
    }

    if (getcwd(cwd, PATH_MAX) != NULL) {
        return cwd;
    } else {
        free(cwd);
        return NULL;
    }
}