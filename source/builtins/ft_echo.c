/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:31:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:28:31 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/minishell.h"

void	ft_echo(char **argument, t_mini *mini)
{
	int	i;
	int	put_break;
	int n;

	i = 1;
	if(argument[1] && ft_strncmp("-n", argument[1], ft_strlen(argument[1])) == 0)
		i = 2;
	put_break = i;
	while (i < numb_split(argument))
	{
		n = 0;
		while (argument[i][n])
		{
			ft_putchar_fd(argument[i][n], STDOUT_FILENO);
			n++;
		}
		if (argument[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if(put_break == 1)
		ft_putchar_fd('\n', 1);
	mini->last_return = 0;
}