/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifying_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:50:52 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:51:34 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

static int	ft_check_quotes(char *str, int i)
{
	int		single_quote;
	int		double_quote;

	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == 34 && single_quote == 0)
		{
			if (double_quote == 0)
				double_quote++;
			else
				double_quote--;
		}
		if (str[i] == 39 && double_quote == 0)
		{
			if (single_quote == 0)
				single_quote++;
			else
				single_quote--;
		}
	}
	return (single_quote == 0 && double_quote == 0);
}

int	ft_verifying_line(char *line)
{
	char	**matrix;
	int		i;

	i = -1;
	matrix = ft_split_advanced(line, " ");
	while (matrix[++i])
	{
		if (!ft_check_quotes(matrix[i], -1))
		{
			ft_free_matrix(matrix);
			return (0);
		}
	}
	ft_free_matrix(matrix);
	return (1);
}
