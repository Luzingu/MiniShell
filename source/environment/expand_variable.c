#include "../../header/minishell.h"

static int ft_get_len_aloc(t_mini *mini, char *input)
{
    int len_aloc;
    char *env_name;
    int i;
    int n;

    len_aloc = 0;
    n = 0;
    while (input[n])
    {
        if (input[n] == '$')
        {
            env_name = malloc(100);
            i = 0;
            while (input[++n] && (ft_isalnum(input[n]) || input[n] == '_'))
                env_name[i++] = input[n];
            env_name[i] = '\0';
            len_aloc += ft_strlen(ft_getenv(mini->env, env_name));
            free(env_name);
        }
        else 
        {
            len_aloc++;
            n++;
        }   
    }
    return (len_aloc);
}

char *expand_variables(t_mini *mini, char *input)
{
    int len_aloc;
    char *expanded;
    char *env_name;
    int i;
    int n;

    len_aloc = ft_get_len_aloc(mini, input);
    expanded = malloc(len_aloc + 1);
    if (!expanded)
        return (NULL);
    n = 0;
    len_aloc = 0;
    while (input[n])
    {
        if (input[n] == '$')
        {
            env_name = malloc(100);
            i = 0;
            while (input[++n] && (ft_isalnum(input[n]) || input[n] == '_'))
                env_name[i++] = input[n];
            env_name[i] = '\0';
            env_name = ft_getenv(mini->env, env_name);
            if (env_name)
            {
                i = 0;
                while (env_name[i])
                    expanded[len_aloc++] = env_name[i++];
            }
        }
        else
            expanded[len_aloc++] = input[n++];
    }
    expanded[len_aloc] = '\0';
    free(input);
    return (expanded);
}