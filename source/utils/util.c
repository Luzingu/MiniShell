/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:40:40 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:57:41 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int numb_split (char **mtx)
{
    int num;

    num = 0;
    while (mtx[num])
        num++;
    return (num);
}

void ft_free_mtrs(char **matriz)
{
    int i;

    if (!matriz)
        return ;
    i = 0;
    while (matriz[i])
    {
        free(matriz[i]);
        i++;
    }
    free(matriz);
}

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

char *my_strndup(const char *s, size_t n)
{
    char *dup;
    size_t i;

    if (!s)
        return (NULL);
    dup = (char *)malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i] != '\0')
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}



