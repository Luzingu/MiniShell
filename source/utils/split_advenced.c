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

#include "../../header/minishell.h"

static size_t count_substrings(const char *s, const char *delimiter)
{
    size_t len = strlen(s);
    size_t delimiter_len = strlen(delimiter);
    size_t count = 0;
    char in_single_quotes = 0;
    char in_double_quotes = 0;

    for (size_t i = 0; i < len; ++i) {
        if (s[i] == '\'') {
            in_single_quotes = !in_single_quotes;
        } else if (s[i] == '\"') {
            in_double_quotes = !in_double_quotes;
        } else if (!in_single_quotes && !in_double_quotes) {
            if (i + delimiter_len <= len && strncmp(s + i, delimiter, delimiter_len) == 0) {
                ++count;
                i += delimiter_len - 1;
            }
        }
    }
    ++count; // Account for the last substring
    return count;
}

static char **allocate_result(size_t count) {
    char **result = (char **)malloc((count + 1) * sizeof(char *));
    if (!result) return NULL;
    result[count] = NULL; // Null-terminate the array
    return result;
}

static int add_substring(char **result, size_t index, const char *start, size_t length) {
    result[index] = strndup(start, length);
    return result[index] != NULL;
}

static int process_substrings(char **result, const char *s, const char *delimiter)
{
    size_t len = strlen(s);
    size_t delimiter_len = strlen(delimiter);
    size_t i = 0, start = 0, current = 0;
    char in_single_quotes = 0;
    char in_double_quotes = 0;

    while (i < len) {
        if (s[i] == '\'') {
            in_single_quotes = !in_single_quotes;
        } else if (s[i] == '\"') {
            in_double_quotes = !in_double_quotes;
        } else if (!in_single_quotes && !in_double_quotes) {
            if (i + delimiter_len <= len && strncmp(s + i, delimiter, delimiter_len) == 0) {
                if (!add_substring(result, current++, s + start, i - start)) {
                    return 0; // Failed to allocate memory
                }
                start = i + delimiter_len;
                i += delimiter_len - 1;
            }
        }
        ++i;
    }
    return add_substring(result, current, s + start, i - start) ? 1 : 0;
}
char **ft_split_advanced(const char *s, const char *delimiter) {
    size_t count = count_substrings(s, delimiter);
    char **result = allocate_result(count);
    if (!result) return NULL;
    
    if (!process_substrings(result, s, delimiter)) {
        free(result);
        return NULL;
    }
    
    return result;
}