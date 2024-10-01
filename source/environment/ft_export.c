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

static char *create_export_string(char *args, char **name_v, char **value)
{
    int i;
    char *str;

    i = whereis(args, "=");
    if (i == -1)
    {
        printf("Erro: '=' não encontrado no argumento.\n");
        return (NULL);
    }
    *name_v = ft_substr(args, 0, i);
    *value = ft_substr(args, i + 1, ft_strlen(args) - i - 1);
    str = ft_strjoin(ft_strjoin(ft_strdup(*name_v), "="), *value);
    return (str);
}

static int update_env(char **env, char **new_env, char *str, char *name_v)
{
    int i = 0;
    int exist = 0;

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
    return (exist);
}

char **ft_export(char *args, char **env)
{
    char *name_v;
    char *value;
    char *str;
    char **new_env;
    int i;
    int exist;

    str = create_export_string(args, &name_v, &value);
    if (!str)
        return (NULL);

    i = 0;
    while (env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (NULL);

    exist = update_env(env, new_env, str, name_v);
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