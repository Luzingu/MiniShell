/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:03:39 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:44:56 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	bubble_sort(char **matrix, int n)
{
	int		swapped;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		swapped = 0;
		while (j < n - i - 1)
		{
			if (strncmp(matrix[j], matrix[j + 1], 100) > 0)
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

void	ft_env(t_env *env)
{
	char	**matrix;
	int		nb_split;
	int		i;

	matrix = env_to_matrix(env, 0);
	nb_split = numb_split(matrix);
	bubble_sort(matrix, nb_split);
	i = -1;
	while (++i < nb_split)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(matrix[i], 1);
	}
	ft_free_matrix(matrix);
}
