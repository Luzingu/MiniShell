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

static void	ft_displaying_error(char **matrix, int flag)
{
	ft_putstr_fd("exit\nminishell: exit: ", 1);
	if (flag)
		ft_putendl_fd("too many arguments", 1);
	else
	{
		ft_putstr_fd(matrix[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
	return ;
}

static void	ft_closing_shell(int exit_status, t_mini *mini)
{
	ft_putendl_fd("exit", 1);
	mini->last_return = exit_status;
	exit(exit_status);
	return ;
}

static int	ft_isvalid_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **matrix, t_mini *mini)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	if (total_of_arguments > 2)
	{
		ft_displaying_error(matrix, 1);
		mini->last_return = 1;
		return ;
	}
	else if (total_of_arguments == 2)
	{
		if (!ft_isvalid_argument(matrix[1]))
			ft_displaying_error(matrix, 0);
		ft_closing_shell(ft_atoi(matrix[1]), mini);
	}
	else
		ft_closing_shell(0, mini);
	return ;
}
