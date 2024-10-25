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

static void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static char	**allocate_matrix(void)
{
	char	**matrix;

	matrix = (char **)malloc(sizeof(char *) * 10000);
	if (!matrix)
		return (NULL);
	return (matrix);
}

static void	process_separator(char *line, int *i, char **matrix, int *j)
{
	char	*str;

	if (is_separator(line[*i]))
	{
		str = get_separator(line, i);
		if (str && str[0])
		{
			if (matrix[*j - 1] && ft_strcmp(matrix[*j - 1], "|") == 0)
				matrix[(*j)++] = ft_strdup("echo");
			matrix[(*j)++] = str;
		}
	}
}

char	**process_str(t_mini *mini, char *line)
{
	int		i;
	int		j;
	char	**matrix;
	char	*str;

	matrix = allocate_matrix();
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		str = return_str(line, &i);
		str = expand_variables(mini, str, 0);
		if (str && str[0])
			matrix[j++] = str;
		skip_whitespace(line, &i);
		process_separator(line, &i, matrix, &j);
	}
	matrix[j] = NULL;
	return (matrix);
}
