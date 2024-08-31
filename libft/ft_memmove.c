/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:08:22 by mcaquart          #+#    #+#             */
/*   Updated: 2024/08/24 18:11:33 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*sr;
	char	*ds;

	i = len;
	ds = (char *)dest;
	sr = (char *)src;
	if (dest == src)
		return (dest);
	else if (ds > sr)
		while (i--)
			ds[i] = sr[i];
	else
		ft_memcpy(dest, src, len);
	return (ds);
}
