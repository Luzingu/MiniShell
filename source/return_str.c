/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_str.c   			                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:27:38 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 02:52:13 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*return_str(char *ptr, int *i)
{
	char	*str;
	int		n;

	n = 0;
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!str)
		return (NULL);
	while (ptr[*i] && !is_separator(ptr[*i]) && ptr[*i] != ' ')
		str[n++] = ptr[(*i)++];
	str[n] = '\0';
	return (str);
}
