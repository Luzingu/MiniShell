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

static t_token	*create_token(t_mini *mini, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = expand_variables(mini, str);
	token->type = 0;
	token->next = NULL;
	return (token);
}

static t_token	*process_token(t_mini *mini, char *str
	, t_token **next, t_token **first_token)
{
	t_token	*new;

	new = create_token(mini, str);
	if (new)
	{
		type_arg(*first_token, new);
		if (*next)
			(*next)->next = new;
		*next = new;
		if (!(*first_token))
			*first_token = new;
	}
	return (*next);
}

static void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static t_token	*process_line(t_mini *mini, char *line)
{
	int		i;
	t_token	*next;
	t_token	*first_token;
	char	*str;

	i = 0;
	next = NULL;
	first_token = NULL;
	while (line[i])
	{
		skip_whitespace(line, &i);
		str = return_str(line, &i);
		if (str && str[0])
			process_token(mini, str, &next, &first_token);
		skip_whitespace(line, &i);
		if (is_separator(line[i]))
		{
			str = get_separator(line, &i);
			if (str && str[0])
				process_token(mini, str, &next, &first_token);
		}
	}
	return (first_token);
}

t_token	*get_tokens(t_mini *mini, char *line)
{
	t_token	*tokens;

	tokens = process_line(mini, line);
	return (tokens);
}
