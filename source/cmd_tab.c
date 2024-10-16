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

char	**cmd_tab(char **tokens, int *pos_token)
{
	char	**tab;
	int	i;
	int	j;

	if (!tokens)
		return (NULL);
	i = *pos_token;
	j = 0;
	while (tokens[i] && !(ft_strcmp(tokens[i], "|") == 0 || ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0))
	{
		i++;
		j++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (tokens[*pos_token] && !(ft_strcmp(tokens[*pos_token], "|") == 0 || ft_strcmp(tokens[*pos_token], "<") == 0 || ft_strcmp(tokens[*pos_token], ">") == 0 || ft_strcmp(tokens[*pos_token], ">>") == 0))
	{
		tab[i++] = ft_strdup(tokens[*pos_token]);
		*pos_token += 1;
	}
	tab[i] = NULL;
	return (tab);
}
