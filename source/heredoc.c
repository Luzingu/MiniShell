/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:38 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:39:08 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	**heredoc(const char *delimiter, int count)
{
	char		**lines;
	char		**new_lines;
	char		*line;
	char		*tmp;
	int		size = 10;

	lines = (char **)malloc(size * sizeof(char *));
	if (!lines)
		exit(EXIT_FAILURE);
	
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_free_matrix(lines);
			return (NULL);
		}
		tmp = ft_strtrim(line, " ");
		if (!tmp)
		{
			ft_free(line, 1);
			ft_free_matrix(lines);
			return (NULL);
		}

		if (ft_strcmp(tmp, delimiter) == 0)
		{
			ft_free(tmp, 1);
			ft_free(line, 1);
			break;
		}

		if (count >= size - 1)
		{
			size *= 2;
			new_lines = (char **)malloc(size * sizeof(char *));
			if (!new_lines)
			{
				ft_free(tmp, 1);
				ft_free(line, 1);
				ft_free_matrix(lines);
				exit(EXIT_FAILURE);
			}
			for (int i = 0; i < count; i++)
				new_lines[i] = lines[i];

			ft_free(lines, 1);
			lines = new_lines;
		}

		lines[count++] = tmp;
		ft_free(line, 1);
	}
	
	lines[count] = NULL;
	return (lines);
}

static void	process_heredoc(const char *delimiter)
{
	char	**lines;
	int		i;

	i = -1;
	lines = heredoc(delimiter, 0);
	if (lines)
	{
		while (lines[++i])
		{
			ft_putstr_fd(lines[i], 1);
			write(1, "\n", 1);
		}
		ft_free_matrix(lines);
	}
}

int	handle_heredoc(char *line)
{
	char	**tokens;
	char	**tokens2;
	char	*delimiter;

	tokens = ft_split_advanced(line, "<<");
	if (tokens[1])
	{
		tokens2 = ft_split(tokens[1], ' ');
		delimiter = tokens2[0];
		if (!ft_strcmp(delimiter, ">") || !ft_strcmp(delimiter, "<")
			|| !ft_strcmp(delimiter, ">>")
			|| !ft_strcmp(delimiter, "<<")
			|| !ft_strcmp(delimiter, "|"))
		{
			ft_free_matrix(tokens);
			ft_free_matrix(tokens2);
			return (2);
		}
		process_heredoc(delimiter);
		ft_free_matrix(tokens);
		ft_free_matrix(tokens2);
		return (1);
	}
	ft_free_matrix(tokens);
	return (0);
}


