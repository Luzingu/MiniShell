/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:40:40 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/04 10:12:27 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_mtrs(char **matriz)
{
    int i;
    if (!matriz)
        return ;
    i = 0;
    while (matriz[i])
    {
        free(matriz[i]);
        i++;
    }
    free(matriz);
}

char    *ft_strcat(char *str1, char *str2)
{
    int i;
    int n;
    char    *str;

    i = ft_strlen(str1) + ft_strlen(str1);
    str = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    n = 0;
    while (str1[n])
        str[i++] = str1[n++];
    n = 0;
    while (str2[n])
        str[i++] = str2[n++];
    str[i] = '\0';
    return (str);
}

void    get_comando(char *str, char **comando, char **argumentos)
{
    int i;
    int tot_c;
    int tot_a;
    char str_fill;
    char *trimmed_str;

    trimmed_str = ft_strtrim((const char *)str, " ");
    if (!trimmed_str)
        return;
    i = 0;
    tot_c = 0;
    tot_a = 0;
    str_fill = 'c';
    while (trimmed_str[i])
    {
        if (str_fill == 'c')
            tot_c++;
        else
            tot_a++;
        if((trimmed_str[i] == ' ' || trimmed_str[i] == '\t') && str_fill == 'c')
            str_fill = 'a';
        i++;
    }
    *comando = (char *)malloc(tot_c + 1);
    *argumentos = (char *)malloc(tot_a + 1);
    if (!*comando || !*argumentos)
    {
        free(trimmed_str);
        return ;
    }
    i = 0;
    tot_c = 0;
    tot_a = 0;
    str_fill = 'c';
    while (trimmed_str[i])
    {
        if (str_fill == 'c')
        {
            (*comando)[tot_c] = trimmed_str[i]; 
            tot_c++;
        }
        else
        {
            (*argumentos)[tot_a] = trimmed_str[i];
            tot_a++;
        }
        if((trimmed_str[i] == ' ' || trimmed_str[i] == '\t') && str_fill == 'c')
            str_fill = 'a';
        i++;
    }
    (*comando)[tot_c] = '\0';
    *comando = ft_strtrim(*comando, " ");
    (*argumentos)[tot_a] = '\0';
    free(trimmed_str);
}


void    execute_ve(char *bin, char *argumentos, char **var_ambiente)
{
    char **args;
    char **str_tmp;
    int tot_args;
    int i;
    int status;
    pid_t  pid_f;

    tot_args = 0;
    str_tmp = ft_split(argumentos, ' ');
    while (str_tmp[tot_args])
        tot_args++;
    args = (char **)malloc(sizeof(char *) * (tot_args + 3));
    args[0] = ft_strdup((const char *)bin);
    i = 0;
    while(i < tot_args)
    {
        args[(i + 1)] = ft_strdup((const char *)str_tmp[i]);
        i++;
    }
    args[(i + 1)] = NULL;

    pid_f = fork();
    if (pid_f == 0)
        execve(args[0], args, var_ambiente);
    else
        waitpid(pid_f, &status, 0);

    ft_free_mtrs(str_tmp);
    ft_free_mtrs(args);
    ft_free_mtrs(var_ambiente);
}