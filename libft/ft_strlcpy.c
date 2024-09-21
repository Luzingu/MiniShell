/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:13 by mcaquart          #+#    #+#             */
/*   Updated: 2024/08/24 18:30:15 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = -1;
	if (destsize)
	{
		while (++i < (destsize - 1) && src[i])
			dest[i] = src[i];
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
