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

static void	process_word(t_mini *mini,
	int *i, char **matrix, int *j)
{
	char	*str;

	skip_whitespace(mini->values.str1, i);
	str = return_str(mini->values.str1, i);
	str = expand_variables(mini, str);
	if (str && str[0])
		matrix[(*j)++] = str;
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

char	**process_str(t_mini *mini)
{
	int		i;
	int		j;
	char	**matrix;

	matrix = allocate_matrix();
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (mini->values.str1[i])
	{
		process_word(mini, &i, matrix, &j);
		skip_whitespace(mini->values.str1, &i);
		process_separator(mini->values.str1, &i, matrix, &j);
	}
	matrix[j] = NULL;
	return (matrix);
}
