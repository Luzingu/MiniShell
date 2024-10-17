/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifying_argument.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:13:48 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 17:13:51 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	verifying_next_type(t_mini *mini, char **matrix, int i)
{
	if (ft_strcmp(matrix[i], ">") == 0 || ft_strcmp(matrix[i], ">>") == 0
		|| ft_strcmp(matrix[i], "<") == 0)
	{
		if (!matrix[i + 1] || (ft_strcmp(matrix[i + 1], ">") == 0
				|| ft_strcmp(matrix[i + 1], ">>") == 0
				|| ft_strcmp(matrix[i + 1], "<") == 0
				|| ft_strcmp(matrix[i + 1], "|") == 0))
		{
			ft_putstr_fd("minishell: "
				"syntax error near unexpected token1", 2);
			if (matrix[i + 1])
				ft_putstr_fd(matrix[i + 1], 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			mini->last_return = 258;
			return (0);
		}
	}
	return (1);
}

static int	verifying_previous_type(t_mini *mini, char **matrix, int i)
{
	if (ft_strcmp(matrix[i], "|") == 0)
	{
		if (!matrix[i + 1] || !matrix[i - 1]
			|| ft_strcmp(matrix[i - 1], ">") == 0
			|| ft_strcmp(matrix[i - 1], ">>") == 0
			|| ft_strcmp(matrix[i - 1], "<") == 0
			|| ft_strcmp(matrix[i - 1], "|") == 0)
		{
			ft_putstr_fd("minishell: "
				"syntax error near unexpected token ", 2);
			ft_putstr_fd(matrix[i], 2);
			ft_putstr_fd("'\n", 2);
			mini->last_return = 258;
			return (0);
		}
	}
	return (1);
}

int	verifying_argument(t_mini *mini, char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (!verifying_next_type(mini, matrix, i)
			|| !verifying_previous_type(mini, matrix, i))
			return (0);
		i++;
	}
	return (1);
}
