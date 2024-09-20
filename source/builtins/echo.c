/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:45 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:29:26 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_echo(char *argument, int fd)
{
	int	i;
	int quote_open;
	char	flag[255] = {0};

	i = 0;
	quote_open = 0;
	if ((argument[i] == 34 || argument[i] == 39) && flag[(int)argument[i]] == 0)
	{
		flag[(int)argument[i]] = 1;
		quote_open = argument[i];
		i++;
	}
	while (argument[i])
	{
		if (argument[i] == quote_open && flag[(int)argument[i]] == 1)
		{
			quote_open = 0;
			//flag[(int)argument[i]] = 0;
			i++;
			continue;
		}
		ft_putchar_fd(argument[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}
