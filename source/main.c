/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:31:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 06:40:47 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

static t_token	*next_run(t_token *token)
{
	while (token && !ft_is_type(token, "cmd"))
	{
		token = token->next;
		if (token && ft_is_type(token, "pipe"))
			token = token->next;
	}
	return (token);
}

static int	verifying_heredoc(t_mini *mini, char *line)
{
	int	heredoc;

	heredoc = handle_heredoc(line);
	if (heredoc == 2)
	{
		mini->last_return = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	}
	return (heredoc);
}

static void	process_line(t_mini *mini, char *line)
{
	t_token	*token;
	int	heredoc;

	if (!line || !line[0])
		return ;
	heredoc = verifying_heredoc(mini, line);
	if (heredoc == 2)
		return ;
	mini->start = get_tokens(mini, line);
	token = next_run(mini->start);
	if (!verifying_argument(mini, token))
	{
		mini->last_return = 258;
		return ;
	}
	mini->charge = 1;
	if (heredoc == 0)
		redir_and_exec(mini, token, 0);
}

static void	init_mini(t_mini *mini)
{
	char	*line;
	int		status;

	status = 0;
	while (mini->exit_status == 0)
	{
		mini->parent = 1;
		mini->start = NULL;
		mini->in = dup(STDIN_FILENO);
		mini->out = dup(STDOUT_FILENO);
		line = readline("minishell> ");
		if (!line)
		{
			mini->exit_status = 1;
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*line)
			add_history(line);
		process_line(mini, line);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &status, 0);
		mini->no_exec = 0;
		if (mini->parent == 0)
			exit(0);
	}
}

int	main(int ac, char **argv, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)argv;
	reset_fds(&mini);
	str_dup_env(env, &mini);
	increment_shell_level(&mini);
	mini.last_return = 0;
	mini.exit_status = 0;
	mini.no_exec = 0;
	handle_signals();
	init_mini(&mini);
	ft_free_all(&mini);
	return (0);
}
