/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:42:04 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:42:05 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*prev_sep(t_token *start, t_token *current)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = start;
	prev = NULL;
	while (tmp != NULL && tmp != current)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
}
