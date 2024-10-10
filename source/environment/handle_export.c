/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:37:37 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:37:39 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_export(char **tmp, t_env **env, t_mini *mini)
{
	int	n;

	n = 0;
	while (tmp[++n])
		ft_export(tmp[n], env);
	(void)mini;
}
