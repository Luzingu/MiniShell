/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:47 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 08:38:41 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **matrix, t_mini *mini)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	if (total_of_arguments >= 3)
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", 1);
		return ;
	}
	else if (matrix[1])
	{
		if (!ft_is_numeric(matrix[1]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", matrix[1]);
			mini->last_return = 255;
		}
		else
			mini->last_return = ft_atoi(matrix[1]);
		mini->exit_status = 1;
	}
	else
	{
		ft_putendl_fd("exit", 1);
		mini->exit_status = 1;
	}
	return ;
}
