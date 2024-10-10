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

static void	ft_closing_shell(int exit_status, t_mini *mini)
{
	ft_putendl_fd("exit", 1);
	mini->last_return = exit_status;
	mini->exit_status = 1;
	exit(exit_status);
}

void	ft_exit(char **matrix, t_mini *mini)
{
	int	total_of_arguments;

	total_of_arguments = numb_split(matrix);
	if (total_of_arguments >= 2)
	{
		ft_putendl_fd("minishell: exit: no options required", 1);
		mini->last_return = 1;
		return ;
	}
	else
		ft_closing_shell(0, mini);
	return ;
}
