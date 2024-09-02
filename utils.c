/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:40:40 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/02 12:18:56 by aluzingu         ###   ########.fr       */
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