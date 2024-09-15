/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:21:06 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/15 18:00:18 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	whereis(const char *str, const char *needle)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i <= (ft_strlen(str) - ft_strlen(needle)))
	{
		j = 0;
		while ((j < ft_strlen(needle)) && (str[i + j] == needle[j]))
			j++;
		if (j == ft_strlen(needle))
			return ((int)i);
	}
	return (-1);
}
