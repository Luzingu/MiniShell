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

    while (i <= (ft_strlen(str) - ft_strlen(needle)))
    {
        j = 0;
        while ((j < ft_strlen(needle)) && (str[i + j] == needle[j]))
            j++;
        if (j == ft_strlen(needle))
            return (int)i;
        i++;
    }
    return (-1);
}

