/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:11:01 by mcaquart          #+#    #+#             */
/*   Updated: 2024/09/15 17:59:39 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit(char **matrix)
{
	if (matrix[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_free_mtrs(matrix);
	}
	else if (matrix[0] && (ft_atoi(matrix[0]) >= 1))
		exit(1);
	exit(0);
}
