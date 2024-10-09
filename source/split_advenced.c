/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_advenced.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:38:28 by aluzingu          #+#    #+#             */
/*   Updated: 2024/10/09 08:29:53 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_split_advanced(const char *s, const char *delimiter)
{
	size_t	count;
	char	**result;

	count = count_substrings(s, delimiter, -1, 0);
	result = allocate_result(count);
	if (!result)
		return (NULL);
	if (!process_substrings(result, s, delimiter, 0))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
