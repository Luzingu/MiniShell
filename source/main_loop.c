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

static void	process_line(t_mini *mini, char *line)
{
	char	*str_heredoc;
	int		verif_heredoc;
	t_token	*tokens;

	line = ft_strtrim(line, " ");
	if (!line || !line[0])
	{
		ft_free(line, 1);
		return ;
	}
	tokens = get_tokens(mini, line);
	str_heredoc = NULL;
	verif_heredoc = verifying_heredoc(mini, tokens, &str_heredoc);
	dup_tokens(mini, tokens, str_heredoc);
	if (verif_heredoc == 258 || !verifying_argument(mini))
	{
		mini->last_return = 258;
		return ;
	}
	mini->charge = 1;
	redir_and_exec(mini, 0, 0);
	ft_free_tokens(tokens);
	ft_free(line, 1);
}

static void	reset_minishell(t_mini *mini)
{
	mini->parent = 1;
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
}

static int	read_line(t_mini *mini, char **line)
{
	*line = readline("minishell> ");
	if (!*line)
	{
		mini->exit_status = 1;
		ft_putendl_fd("exit", 2);
		return (0);
	}
	if (**line)
		add_history(*line);
	return (1);
}

void	main_loop(t_mini *mini)
{
	char	*line;
	int		status;

	while (mini->exit_status == 0)
	{
		mini->tokens = NULL;
		reset_minishell(mini);
		if (!read_line(mini, &line))
			break ;
		process_line(mini, line);
		ft_free(line, 1);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &status, 0);
		mini->no_exec = 0;
		if (mini->parent == 0)
			exit(0);
		ft_free_tokens(mini->tokens);
	}
	free_env(mini->env);
}
