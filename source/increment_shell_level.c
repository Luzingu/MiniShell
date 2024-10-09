/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:48:44 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:48:45 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	increment_shell_level(t_mini *mini)
{
	char	*str_shell_level;
	int		shell_level;

	str_shell_level = ft_getenv(mini->env, "SHLVL");
	if (!str_shell_level)
		return ;
	else
	{
		shell_level = ft_atoi(str_shell_level);
		shell_level++;
	}
	ft_export(ft_strjoin("SHLVL=", ft_itoa(shell_level)), &mini->env);
}
