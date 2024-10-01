/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:17:11 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:16:37 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
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

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;
	char	**cmd;

	prev = prev_sep(token, 0);
	next = next_sep(token, 0);
	pipe = 0;
	if (prev && ft_is_type(prev, "trunc"))
		redir(mini, token, "trunc");
	else if (prev && ft_is_type(prev, "append"))
		redir(mini, token, "append");
	else if (ft_is_type(prev, "input"))
		input(mini, token);
	else if (ft_is_type(prev, "pipe"))
		pipe = minipipe(mini);
	if (next && pipe != 1)
		redir_and_exec(mini, next->next);
	if (( !prev || ft_is_type(prev, "pipe"))
		&& pipe != 1 && mini->no_exec == 0)
	{
		cmd = cmd_tab(token);
		if(is_builtin(cmd[0]))
			exec_builtin(cmd, mini);
		else
			execute_cmd(mini, cmd);
		ft_free_matrix(cmd);
	}
}

