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

static char **allocate_result(size_t count)
{
    char **result;
    
    result = (char **)malloc((count + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    result[count] = NULL;
    return (result);
}

static int add_substring(char **result, size_t index, const char *start, size_t length)
{
    result[index] = my_strndup(start, length);
    return (result[index] != NULL);
}

static int process_loop(char **result, const char *s, const char *delimiter, size_t len, size_t delimiter_len)
{
    char in_single_quotes = 0;
    char in_double_quotes = 0;
    size_t i = 0;
    size_t start = 0;
    size_t current = 0;

    while (i < len)
    {
        toggle_quotes(s[i], &in_single_quotes, &in_double_quotes);
        if (!in_single_quotes && !in_double_quotes)
        {
            if (check_delimiter(s, delimiter, len, delimiter_len, &i))
            {
                if (!add_substring(result, current++, s + start, i - start))
                    return 0;
                start = i + delimiter_len;
            }
        }
        i++;
    }
    return (add_substring(result, current, s + start, i - start));
}

static int process_substrings(char **result, const char *s, const char *delimiter)
{
    size_t len = strlen(s);
    size_t delimiter_len = strlen(delimiter);
    return (process_loop(result, s, delimiter, len, delimiter_len));
}

char **ft_split_advanced(const char *s, const char *delimiter)
{
    size_t count;
    char **result;

    count = count_substrings(s, delimiter);
    result = allocate_result(count);
    if (!result)
        return (NULL);
    if (!process_substrings(result, s, delimiter))
    {
        free(result);
        return (NULL);
    }
    return (result);
}