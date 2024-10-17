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

#include "../../header/minishell.h"

static char	**allocate_lines(int size)
{
	char	**lines;

	lines = (char **)malloc(size * sizeof(char *));
	if (!lines)
		exit(EXIT_FAILURE);
	return (lines);
}

static char	*get_trimmed_line(void)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, " ");
	ft_free(line, 1);
	return (tmp);
}

static void	handle_memory_error(char *line, char *tmp, char **lines)
{
	ft_free(tmp, 1);
	ft_free(line, 1);
	ft_free_matrix(lines);
	exit(EXIT_FAILURE);
}

static char	**resize_lines(char **lines, int *size, int count)
{
	char	**new_lines;
	int		i;

	*size *= 2;
	i = -1;
	new_lines = allocate_lines(*size);
	while (++i < count)
		new_lines[i] = lines[i];
	ft_free(lines, 1);
	return (new_lines);
}

char	**heredoc(const char *delimiter, int count)
{
	int		size;
	char	**lines;
	char	*tmp;

	size = 10;
	lines = allocate_lines(size);
	while (1)
	{
		tmp = get_trimmed_line();
		if (!tmp)
			handle_memory_error(NULL, NULL, lines);
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			ft_free(tmp, 1);
			break ;
		}
		if (count >= size - 1)
			lines = resize_lines(lines, &size, count);
		lines[count++] = tmp;
	}
	lines[count] = NULL;
	return (lines);
}
