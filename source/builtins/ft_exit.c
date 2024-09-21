/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:47 by mcaquart          #+#    #+#             */
/*   Updated: 2024/09/21 03:35:07 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ft_displaying_error(char **matrix, int flag)
{
	printf("exit\nbash: exit: ");
	if (flag)
		printf("too many arguments\n");
	else
		printf("%s: %s\n", matrix[1], "numeric argument required");
	ft_free_matrix(matrix);
	return ;
}

static void	ft_closing_shell(int argument)
{
	ft_putendl_fd("exit", 2);
	exit(argument);
}

static void	ft_isvalid(char **matrix)
{
	int	i;

	i = -1;
	while (ft_isalpha(matrix[1][++i]))
		ft_displaying_error(matrix, 0);
	i = 0;
	if (matrix[1][i] == '-' || matrix[1][i] == '+')
		i++;
	while (matrix[1][i])
	{
		if (!ft_isdigit(matrix[1][i]))
			ft_displaying_error(matrix, 0);
		i++;
	}
}

void	ft_exit(char **matrix)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	if (total_of_arguments > 2)
	{
		ft_isvalid(matrix);
		ft_displaying_error(matrix, 1);
	}
	else if (total_of_arguments == 2)
	{
		ft_isvalid(matrix);
		if (ft_atoi(matrix[1]) >= 1)
			ft_closing_shell(1);
		else
			ft_closing_shell(0);
	}
	else
		ft_closing_shell(0);
}
