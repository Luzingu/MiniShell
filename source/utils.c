/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:23:08 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 17:23:10 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int numb_split (char **matrix)
{
    int num;

    num = 0;
    while (matrix[num])
        num++;
    return (num);
}

t_env *add_envirenoment(char *env_name, char *env_value)
{
    t_env *new;
    
    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(env_name);
    new->value = ft_strdup(env_value);
    new->next = NULL;
    return (new);
}

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

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


char **env_to_matrix(t_env *env)
{
    t_env *env_tmp;
    char **matrix;
    char *tmp;
    int i;

    env_tmp = env;
    i = 0;
    while (env_tmp)
    {
        i++;
        env_tmp = env_tmp->next;
    }
    matrix = (char **)malloc(sizeof(char *) * (i + 1));
    env_tmp = env;
    i = 0;
    while (env_tmp)
    {
        tmp = ft_strdup(env_tmp->key);
        tmp = ft_strjoin(tmp, "=");
        tmp = ft_strjoin(tmp, env_tmp->value);
        if (tmp)
        {
            matrix[i] = tmp;
            i++;
        }
        env_tmp = env_tmp->next;
    }
    matrix[i] = NULL;
    return (matrix);
}

char *my_strndup(const char *s, size_t n)
{
    char *dup;
    size_t i;

    if (!s)
        return (NULL);
    dup = (char *)malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i] != '\0')
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
