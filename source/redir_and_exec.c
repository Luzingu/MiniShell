/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:17:11 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 06:56:47 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static t_token	*next_sep(t_token *token)
{
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->next;
	return (token);
}

static int	is_builtin(char *command)
{
	return (!ft_strncmp(command, "echo", ft_strlen(command))
		|| !ft_strncmp(command, "cd", ft_strlen(command))
		|| !ft_strncmp(command, "pwd", ft_strlen(command))
		|| !ft_strncmp(command, "env", ft_strlen(command))
		|| !ft_strncmp(command, "export", ft_strlen(command))
		|| !ft_strncmp(command, "unset", ft_strlen(command))
		|| !ft_strncmp(command, "exit", ft_strlen(command)));
}

void	redir_and_exec(t_mini *mini, t_token *token, int pipe)
{
	t_token	*prev;
	t_token	*next;
	char	**cmd;

	prev = prev_sep(mini->start, token);
	next = next_sep(token);
	if (prev && ft_is_type(prev, "trunc"))
		redir(mini, token, "trunc");
	else if (prev && ft_is_type(prev, "append"))
		redir(mini, token, "append");
	else if (ft_is_type(prev, "input"))
		input(mini, token);
	else if (ft_is_type(prev, "pipe"))
		pipe = minipipe(mini);
	if (next && pipe != 1)
		redir_and_exec(mini, next->next, 0);
	if ((!prev || ft_is_type(prev, "pipe")) && pipe != 1 && mini->no_exec == 0)
	{
		cmd = cmd_tab(token, 2);
		if (is_builtin(cmd[0]))
			exec_builtin(cmd, mini);
		else
			execute_cmd(mini, cmd);
		ft_free_matrix(cmd);
	}
}
