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

int	ft_quote_is_closed(char *str, int i, int quote)
{
	while (str[i])
	{
		if (str[i] == quote && str[i + 1] != quote)
			return (0);
		i++;
	}
	return (1);
}

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
		if (ptr[*i] == 34 && !single_quote)
		{
			if (!double_quote)
			{
				if (ft_quote_is_closed(ptr, *i, 34))
					double_quote = !double_quote;
			}
			else
				double_quote = !double_quote;
		}
		else if (ptr[*i] == 39 && !double_quote)
		{
			if (!single_quote)
			{
				if (ft_quote_is_closed(ptr, *i, 39))
					single_quote = !single_quote;
			}
			else
				single_quote = !single_quote;
		}
		if (!double_quote && !single_quote
			&& (is_separator(ptr[*i]) || ptr[*i] == ' '))
			break ;
		str[n++] = ptr[(*i)++];
	}
	str[n] = '\0';
	return (str);
}
