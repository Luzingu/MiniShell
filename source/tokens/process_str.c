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

static void	process_separator(char *line, int *i, t_token *matrix, int *j)
{
	char	*str;

	if (is_separator(line[*i]))
	{
		str = get_separator(line, i);
		if (str && str[0])
		{
			if (matrix[*j - 1].str && is_type(matrix[*j - 1], 'P'))
			{
				matrix[(*j)].str = ft_strdup("echo");
				matrix[(*j)].type = 'A';
				(*j)++;
			}
			matrix[(*j)].str = str;
			matrix[(*j)].type = type_str(str, 0);
			(*j)++;
		}
	}
}

t_token	*process_str(t_mini *mini, char *line)
{
	int		i;
	int		j;
	int		in_quotes;
	char	*str;

	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	ft_memset(tokens, 0, sizeof(t_token) * 10000);
	while (line[i])
	{
		skip_whitespace(line, &i);
		str = return_str(line, &i, &in_quotes);
		str = expand_variables(mini, str, 0);
		if (str && str[0])
		{
			tokens[j].str = ft_strdup(str);
			tokens[j].type = type_str(str, in_quotes);
			j++;
		}
		skip_whitespace(line, &i);
		process_separator(line, &i, tokens, &j);
		ft_free(str, 1);
	}
	tokens[j].str = NULL;
	return (tokens);
}
