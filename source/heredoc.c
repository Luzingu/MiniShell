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
	char		*line;

	lines = malloc(BUFFER_SIZE * sizeof(char *));
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
		line = ft_strtrim(line, " ");
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		lines[count++] = line;
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
		if (!ft_strncmp(delimiter, ">", 1) || !ft_strncmp(delimiter, "<", 1)
			|| ft_strncmp(delimiter, ">>", 2) == 0
			|| ft_strncmp(delimiter, "<<", 2) == 0
			|| ft_strncmp(delimiter, "|", 1) == 0)
			return (2);
		process_heredoc(delimiter);
		ft_free_matrix(tokens);
		return (1);
	}
	ft_free_matrix(tokens);
	return (0);
}
