#include "../header/minishell.h"

t_env *add_envirenoment(char *env_name, char *env_value)
{
    t_env *new;
    
    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(env_name);
    new->value = ft_strdup(env_value);
    new->next = NULL;
    return (new);
}
