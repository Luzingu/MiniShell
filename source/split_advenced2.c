/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_advenced.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:38:28 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:58:30 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void toggle_quotes(char c, char *in_single_quotes, char *in_double_quotes)
{
    if (c == 39)
        *in_single_quotes = !*in_single_quotes;
    else if (c == 34)
        *in_double_quotes = !*in_double_quotes;
}

int check_delimiter(const char *s, const char *delimiter, size_t len, size_t delimiter_len, size_t *i)
{
    if (*i + delimiter_len <= len && ft_strncmp(s + *i, delimiter, delimiter_len) == 0)
    {
        *i += delimiter_len - 1;
        return (1);
    }
    return (0);
}

size_t count_loop(const char *s, const char *delimiter, size_t len, size_t delimiter_len)
{
    char in_single_quotes = 0;
    char in_double_quotes = 0;
    size_t i = 0;
    size_t count = 0;

    while (i < len)
    {
        toggle_quotes(s[i], &in_single_quotes, &in_double_quotes);
        if (!in_single_quotes && !in_double_quotes)
        {
            if (check_delimiter(s, delimiter, len, delimiter_len, &i))
                count++;
        }
        i++;
    }
    return (count);
}

size_t count_substrings(const char *s, const char *delimiter)
{
    size_t len = strlen(s);
    size_t delimiter_len = strlen(delimiter);
    size_t count = 0;
    count += count_loop(s, delimiter, len, delimiter_len);
    return (count + 1);
}