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

#include "../header/minishell.h"

static void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static char	**process_line(t_mini *mini, char *line)
{
	int		i;
	int		j;
	char	*str;
	char	**matrix;

	matrix = (char **)malloc(sizeof(char *) * 10000);
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		str = return_str(line, &i);
		str = expand_variables(mini, str);
		if (str && str[0])
			matrix[j++] = str;
		skip_whitespace(line, &i);
		if (is_separator(line[i]))
		{
			str = get_separator(line, &i);
			if (str && str[0])
			{
				if (matrix[j - 1] && ft_strcmp(matrix[j - 1], "|") == 0)
					matrix[j++] = ft_strdup("echo");
				matrix[j++] = str;
			}
		}
	}
	matrix[j] = NULL;
	return (matrix);
}

char	**organize_tokens(char **matrix)
{
	int	i;
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

	matrix = process_line(mini, line);
	matrix = organize_tokens(matrix);
	return (matrix);
}


