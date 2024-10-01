/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:10 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:47:07 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/minishell.h"

char **ft_export(char *args, char **env)
{
    char *name_v;
    char *value;
    int i;
    char **new_env;
    int exist = 0;
    char *str;

    i = whereis(args, "=");
    if (i == -1)
    {
        printf("Erro: '=' não encontrado no argumento.\n");
        return (NULL);
    }
    name_v = ft_substr(args, 0, i);
    value = ft_substr(args, i + 1, ft_strlen(args) - i - 1);
    str = ft_strdup(name_v);
    str = ft_strjoin(str, "=");
    str = ft_strjoin(str, value);
    i = 0;
    while (env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        printf("Erro ao alocar memória.\n");
        return (NULL);
    }

    i = 0;
    exist = 0;
    while (env[i])
    {
        if (ft_strncmp(name_v, env[i], ft_strlen(name_v)) == 0 && env[i][ft_strlen(name_v)] == '=')
        {
            new_env[i] = ft_strdup(str);
            exist = 1;
        }
        else
            new_env[i] = ft_strdup(env[i]);
        i++;
    }
    if (!exist)
        new_env[i++] = ft_strdup(str);
    new_env[i] = NULL;
    ft_free_matrix(env);
    free(name_v);
    free(value);
    free(str);
    return (new_env);
}

void handle_export(char **tmp, char ***env)
{
    int n = 1;
    while (tmp[n])
    {
        *env = ft_export(tmp[n], *env);
        n++;
    }
}