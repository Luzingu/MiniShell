/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:26:44 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 08:53:26 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**organize_tokens(char **matrix)
{
	int		i;
	char	*tmp[3];

	i = 0;
	while (matrix[i])
	{
		if ((ft_strcmp(matrix[i], ">") == 0 || ft_strcmp(matrix[i], ">>") == 0))
		{
			if (matrix[i + 2] && !is_separator_str(matrix[i + 2]))
			{
				tmp[0] = matrix[i];
				tmp[1] = matrix[i + 1];
				tmp[2] = matrix[i + 2];
				matrix[i] = tmp[2];
				matrix[i + 1] = tmp[0];
				matrix[i + 2] = tmp[1];
				i = 0;
			}
		}
		i++;
	}
	return (matrix);
}

char	**get_tokens(t_mini *mini, char *line)
{
	char	**matrix;

	matrix = process_str(mini, line);
	matrix = organize_tokens(matrix);
	return (matrix);
}
