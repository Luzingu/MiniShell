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

static int	ft_check_quotes(char *str)
{
	int		i;
	int		n_quote;
	char	quote_check;

	i = -1;
	n_quote = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_check = str[i];
			break ;
		}
	}
	i = -1;
	while (str[++i])
		if (str[i] == quote_check)
			n_quote++;
	return (n_quote % 2 == 0);
}

static char	get_quote_check(char *str)
{
	int		i;
	char	quote_check;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_check = str[i];
			return (quote_check);
		}
	}
	return (0);
}

static char	*verified_line(char *line, char **matrix, char quote,
	int *line_length)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * ((*line_length) + numb_split(matrix)));
	*line_length = 0;
	i = -1;
	while (matrix[++i])
	{
		quote = get_quote_check(matrix[i]);
		j = -1;
		while (matrix[i][++j])
			if (matrix[i][j] != quote)
				new_line[(*line_length)++] = matrix[i][j];
		if (matrix[i + 1])
			new_line[(*line_length)++] = ' ';
	}
	new_line[(*line_length)] = '\0';
	ft_free_matrix(matrix);
	free(line);
	return (new_line);
}

char	*ft_verifying_line(char *line)
{
	char	**matrix;
	char	quote_check;
	int		line_length;
	int		i;
	int		j;

	i = -1;
	matrix = ft_split_advanced(line, " ");
	while (matrix[++i])
		if (!ft_check_quotes(matrix[i]))
			return (NULL);
	i = -1;
	line_length = 0;
	while (matrix[++i])
	{
		quote_check = get_quote_check(matrix[i]);
		j = -1;
		while (matrix[i][++j])
			if (matrix[i][j] != quote_check)
				line_length++;
	}
	return (verified_line(line, matrix, quote_check, &line_length));
}
