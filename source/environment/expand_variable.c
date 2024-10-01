#include "../../header/minishell.h"

static int get_variable_length(t_mini *mini, char *input, int *n)
{
    char *env_name;
    int i = 0;
    int len_aloc = 0;

    if (input[*n] == '?')
    {
        len_aloc += ft_strlen(ft_itoa(mini->last_return));
        (*n)++;
    }
    else
    {
        env_name = malloc(100);
        if (!env_name)
            return (0);
        while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
            env_name[i++] = input[(*n)++];
        env_name[i] = '\0';
        len_aloc += ft_strlen(ft_getenv(mini->env, env_name));
        free(env_name);
    }
    return (len_aloc);
}

static int ft_get_len_aloc(t_mini *mini, char *input)
{
    int len_aloc = 0;
    int n = 0;

    while (input[n])
    {
        if (input[n] == '$')
        {
            n++;
            len_aloc += get_variable_length(mini, input, &n);
        }
        else
        {
            len_aloc++;
            n++;
        }
    }
    return (len_aloc);
}

char *get_env_value(t_mini *mini, char *input, int *n)
{
    char *env_name;
    int i = 0;

    if (input[*n] == '?')
    {
        env_name = ft_itoa(mini->last_return);
        (*n)++;
    }
    else
    {
        env_name = malloc(100);
        if (!env_name)
            return (NULL);
        while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
            env_name[i++] = input[(*n)++];
        env_name[i] = '\0';
        env_name = ft_getenv(mini->env, env_name);
    }
    return (env_name);
}

char *expand_variables(t_mini *mini, char *input)
{
    int len_aloc;
    char *expanded;
    char *env_value;
    int n = 0, i;

    len_aloc = ft_get_len_aloc(mini, input);
    expanded = malloc(len_aloc + 1);
    if (!expanded)
        return (NULL);
    len_aloc = 0;
    while (input[n])
    {
        if (input[n] == '$')
        {
            n++;
            env_value = get_env_value(mini, input, &n);
            if (env_value)
            {
                i = 0;
                while (env_value[i])
                    expanded[len_aloc++] = env_value[i++];
            }
        }
        else
            expanded[len_aloc++] = input[n++];
    }
    expanded[len_aloc] = '\0';
    free(input);
    return (expanded);
}
