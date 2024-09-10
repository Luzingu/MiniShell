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



void	ft_echo(char *argument)
{
	int	i;

	i = 0;
	if (argument[i] == 34 || argument[i] == 39)
		i++;
	while (argument[i])
	{
		if (argument[i] == 34 || argument[i] == 39)
			break ;
		ft_putchar_fd(argument[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	ft_exit(char **matrix)
{
	if (matrix[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_free_mtrs(matrix);
		return ;
	}
	else if (matrix[0] && (ft_atoi(matrix[0]) >= 1))
		exit(1);
	exit(0);
}


void	ft_cat(char **argument)
{
	int	fd;

	fd = open(argument[0], 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp("cat", argument);
}


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

void get_command(char *str, char **command, char **argument)
{
    int i, total, length;
    char	**matrix;

    matrix = ft_split(str, ' ');
    if (!matrix)
        return;
    if (matrix[0])
        *command = ft_strdup(matrix[0]);
    else
        *command = NULL;
    total = 0;
    i = 0;
    while (matrix[++i])
    	total += (int)ft_strlen(matrix[i]) + 1;
    *argument = (char *)malloc(total + 1);
    if (!(*argument))
    {
        ft_free_mtrs(matrix);
        return ;
    }
    length = 0;
    i = 0;
    while (matrix[++i])
    {
        strcpy(*argument + length, matrix[i]);
        length += strlen(matrix[i]);
        if (matrix[i + 1])
            (*argument)[length++] = ' ';
    }
    (*argument)[length] = '\0';
    ft_free_mtrs(matrix);
}


void    execute_ve(char *bin, char *argument, char **var_ambiente)
{
    pid_t	pid_f;
    int		total_arguments;
    int		i;
    int		status;
    char	**args;
    char	**str_tmp;

    total_arguments = 0;
    str_tmp = ft_split(argument, ' ');
    while (str_tmp[total_arguments])
        total_arguments++;
    args = (char **)malloc(sizeof(char *) * (total_arguments + 3));
    args[0] = ft_strdup((const char *)bin);
    i = -1;
    while(++i < total_arguments)
        args[(i + 1)] = ft_strdup((const char *)str_tmp[i]);
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
