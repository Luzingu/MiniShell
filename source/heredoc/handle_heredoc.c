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

static void	process_heredoc(t_mini *mini, const char *delimiter)
{
	char	**lines;
	int		i;

	i = -1;
	lines = heredoc(mini, delimiter, 0);
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

int	handle_heredoc(t_mini *mini, char *line)
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
		process_heredoc(mini, delimiter);
		ft_free_matrix(tokens);
		ft_free_matrix(tokens2);
		return (1);
	}
	ft_free_matrix(tokens);
	return (0);
}
