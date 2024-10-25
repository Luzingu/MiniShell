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

static int	is_builtin(char *command)
{
	return (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "exit"));
}

void	ft_execute(t_mini *mini, int *pos_token)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(mini->tokens, pos_token);
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, mini);
	else
		execute_cmd(mini, cmd);
	ft_free_matrix(cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

void	redir_and_exec(t_mini *mini, int pos_token, int pipe)
{
	char	*prev;

	prev = NULL;
	if (pos_token > 0)
		prev = mini->tokens[pos_token - 1];
	if (ft_strcmp(prev, ">") == 0)
		redir(mini, mini->tokens[pos_token], "trunc");
	else if (ft_strcmp(prev, ">>") == 0)
		redir(mini, mini->tokens[pos_token], "append");
	else if (ft_strcmp(prev, "<") == 0)
		input(mini, mini->tokens[pos_token]);
	else if (ft_strcmp(prev, "|") == 0)
		pipe = minipipe(mini);
	if (mini->tokens[(pos_token + 1)] && pipe != 1)
		redir_and_exec(mini, (pos_token + 1), 0);
	if ((!prev || ft_strcmp(prev, "|") == 0) && pipe != 1 && mini->no_exec == 0)
		ft_execute(mini, &pos_token);
} 
