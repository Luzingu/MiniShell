/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:11:01 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:29:31 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit(char **matrix)
{
	if (matrix[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_free_mtrs(matrix);
		return ;
	}
	else if (matrix[0] && (ft_atoi(matrix[0]) >= 1))
		exit(1);
	exit(0);
}
