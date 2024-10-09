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
	bool	double_quote;
	bool	single_quote;

	n = 0;
	str = (char *)malloc(sizeof(char) * 100000);
	if (!str)
		return (NULL);
	double_quote = false;
	single_quote = false;
	while (ptr[*i])
	{
		if (ptr[*i] == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (ptr[*i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (!double_quote && !single_quote && (is_separator(ptr[*i]) || ptr[*i] == ' '))
			break;
		str[n++] = ptr[(*i)++];
	}
	str[n] = '\0';
	return (str);
}

