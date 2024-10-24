/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:16:13 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:16:15 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	numb_split(char **matrix)
{
	int	num;

	num = 0;
	while (matrix[num])
		num++;
	return (num);
}
