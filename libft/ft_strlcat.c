/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:44:10 by mcaquart          #+#    #+#             */
/*   Updated: 2024/05/17 03:23:56 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	column;

	i = 0;
	column = -1;
	while (dst[i] && size > i)
		i++;
	while (src[++column] && size > (i + column + 1))
		dst[i + column] = src[column];
	if (size > i)
		dst[i + column] = '\0';
	return (i + ft_strlen(src));
}
