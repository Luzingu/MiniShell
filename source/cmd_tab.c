/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:20 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:26:24 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**cmd_tab(t_token *start, int i)
{
	t_token	*token;
	char	**tab;

	if (!start)
		return (NULL);
	token = start->next;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
} 
