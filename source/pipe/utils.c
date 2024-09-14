/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:21:06 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:29:20 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int whereis(const char *str, const char *needle)
{
    size_t i = 0;
    size_t j;
    size_t str_len = 0;
    size_t needle_len = 0;

    while (str[str_len] != '\0')
        str_len++;
    while (needle[needle_len] != '\0')
        needle_len++;
    while (i <= str_len - needle_len)
    {
        j = 0;
        while (j < needle_len && str[i + j] == needle[j])
            j++;
        if (j == needle_len)
            return (int)i;
        i++;
    }
    return (-1);
}

