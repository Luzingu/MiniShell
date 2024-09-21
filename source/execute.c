/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:12:39 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:57:36 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*get_command_from_matrix(char **matrix)
{
    if (matrix[0])
        return ft_strdup(matrix[0]);
    return NULL;
}

static void	concatenate_arguments(char **matrix, char *argument)
{
	int		i;
	size_t	length;

	i = 0;
	length = 0;
	while (matrix[++i])
	{
		strcpy(argument + length, matrix[i]);
		length += ft_strlen(matrix[i]);
		if (matrix[i + 1])
			argument[length++] = ' ';
	}
	argument[length] = '\0';
}

void	get_command(char *str, char **command, char **argument)
{
	int		total;
	char	**matrix;

	*command = NULL;
	*argument = NULL;
	matrix = ft_split(str, ' ');
	if (!matrix)
		return ;
	*command = get_command_from_matrix(matrix);
	total = numb_split(matrix);
	*argument = (char *)malloc(total + 1);
	if (!(*argument))
	{
		ft_free_matrix(matrix);
		return ;
	}
	concatenate_arguments(matrix, *argument);
	ft_free_matrix(matrix);
}

void    execute_ve(char *bin, char *argument, char **var_ambiente)
{
	int		total_arguments;
	int		i;
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
	execve(args[0], args, var_ambiente);
	ft_free_matrix(str_tmp);
	ft_free_matrix(args);
	ft_free_matrix(var_ambiente);
}
