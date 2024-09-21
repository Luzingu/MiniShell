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

int	numb_split(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char **matrix)
{
    int	i;

    if (!matrix)
        return ;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

char	*ft_strcat(char *str1, char *str2)
{
    int		i;
    int		n;
    char	*str;

    str = malloc(sizeof(char) * ((ft_strlen(str1) + ft_strlen(str1)) + 1));
    i = 0;
    n = 0;
    while (str1[n])
        str[i++] = str1[n++];
    n = 0;
    while (str2[n])
        str[i++] = str2[n++];
    str[i] = '\0';
    return (str);
}
