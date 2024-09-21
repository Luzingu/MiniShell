/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:18:44 by mcaquart          #+#    #+#             */
/*   Updated: 2024/08/24 18:39:38 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = malloc(sizeof(char *) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, (ft_strlen(s1) + 1));
	return (s2);
}
