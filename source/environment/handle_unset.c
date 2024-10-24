/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:12:57 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:12:59 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_unset(char **tmp, t_env **env)
{
	int	n;

	n = -1;
	while (tmp[++n])
		ft_unset(tmp[n], env);
	return (0);
}
