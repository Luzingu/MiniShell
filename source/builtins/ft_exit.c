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
	{
		ft_putendl_fd("exit", 1);
		mini->exit_status = 1;
	}
	return ;
}
