/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:33:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/08/30 16:55:57 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	int		x;
	int		y;
	char	**matrix;

	while (*s && (*s == c))
		s++;
	matrix = malloc(2 * (ft_strlen(s) + 1));
	y = 0;
	while (*s)
	{
		x = 0;
		matrix[y] = malloc(2 * (ft_strlen(s) + 1));
		while (*s && !(*s == c))
			matrix[y][x++] = *(s++);
		while (*s && (*s == c))
			s++;
		matrix[y++][x] = '\0';
	}
	matrix[y] = NULL;
	return (matrix);
}
