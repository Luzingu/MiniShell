/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_advenced_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:24:41 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 08:29:49 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

static int	add_substring(char **result, size_t index, const char *start,
	size_t length)
{
	result[index] = my_strndup(start, length);
	return (result[index] != NULL);
}

static int	verifying_quotes(char c)
{
	char	in_single_quotes;
	char	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	if (c == '\'')
		in_single_quotes = !in_single_quotes;
	else if (c == '\"')
		in_double_quotes = !in_double_quotes;
	return ((!in_single_quotes && !in_double_quotes));
}

int	process_substrings(char **result, const char *s, const char *delimiter,
	size_t start)
{
	size_t	i;
	size_t	current;

	i = -1;
	current = 0;
	while (++i < ft_strlen(s))
	{
		if (verifying_quotes(s[i]))
		{
			if (i + ft_strlen(delimiter) <= ft_strlen(s)
				&& !ft_strncmp(s + i, delimiter, ft_strlen(delimiter)))
			{
				return (add_substring(result, current++, s + start, i - start));
				start = i + ft_strlen(delimiter);
				i += ft_strlen(delimiter) - 1;
			}
		}
	}
	return (add_substring(result, current, s + start, i - start));
}

size_t	count_substrings(const char *s, const char *delimiter, size_t i,
	size_t count)
{
	char	in_single_quotes;
	char	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while (++i < ft_strlen(s))
	{
		if (s[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (s[i] == '\"')
			in_double_quotes = !in_double_quotes;
		else if (!in_single_quotes && !in_double_quotes)
		{
			if (i + ft_strlen(delimiter) <= ft_strlen(s)
				&& !ft_strncmp(s + i, delimiter, ft_strlen(delimiter)))
			{
				++count;
				i += ft_strlen(delimiter) - 1;
			}
		}
	}
	++count;
	return (count);
}

char	**allocate_result(size_t count)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
