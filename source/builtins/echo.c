/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:45 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/15 17:59:20 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_echo(char *argument, int fd)
{
	int	i;
	int	quote_open;

	i = -1;
	quote_open = 0;
	if (argument[++i] == 34 || argument[i] == 39)
		quote_open = argument[i];
	while (argument[i])
	{
		if (argument[i] == quote_open)
		{
			quote_open = argument[i];
			i++;
			continue ;
		}
		if ((argument[i] == 34 || argument[i] == 39) && !argument[i + 1])
			break ;
		ft_putchar_fd(argument[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}
