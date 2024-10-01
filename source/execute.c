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

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->prev;
	return (token);
}

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

void	exec_cmd(t_mini *mini, char **cmd)
{
	pid_t pid;
	int	status;

	if (mini->charge == 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		char *cmd_path = ft_strjoin("/bin/", cmd[0]);
		execve(cmd_path, cmd, mini->env);
	}
	else
		waitpid(pid, &status, 0);
	mini->charge = 0;
}

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	cmd[1] ? ft_putendl_fd("❤️", STDERR) : ft_putendl_fd("💚", STDERR);
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
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
	if (prev && ft_strncmp(prev->type, "trunc", ft_strlen(prev->type)) == 0)
		redir(mini, token, "trunc");
	else if (prev && ft_strncmp(prev->type, "append", ft_strlen(prev->type)) == 0)
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
			exec_cmd(mini, cmd);
		free_tab(cmd);
	}
}

