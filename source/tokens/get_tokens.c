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

t_token	*organize_tokens(t_token *tokens)
{
	int		i;
	t_token	tmp[3];

	i = -1;
	while (tokens[++i].str)
	{
		if (is_type(tokens[i], 'R') || is_type(tokens[i], 'T')
			|| is_type(tokens[i], 'H') || is_type(tokens[i], 'I'))
		{
			if (tokens[i + 2].str && is_type(tokens[i + 2], 'A'))
			{
				tmp[0] = tokens[i];
				tmp[1] = tokens[i + 1];
				tmp[2] = tokens[i + 2];
				tokens[i] = tmp[2];
				tokens[i + 1] = tmp[0];
				tokens[i + 2] = tmp[1];
				i = 0;
			}
		}
	}
	return (tokens);
}

t_token	*get_tokens(t_mini *mini, char *line)
{
	t_token	*tokens;

	tokens = process_str(mini, line);
	tokens = organize_tokens(tokens);
	return (tokens);
}
