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


int	verifying_heredoc(t_mini *mini, t_token *tokens, char **str_heredoc)
{
	t_token	delimiter;
	int		i;

	i = 0;
	*str_heredoc = NULL;
	while (tokens[i].str)
	{
		if (is_type(tokens[i], 'H'))
		{
			if (tokens[i + 1].str)
			{
				delimiter = tokens[i + 1];
				if (is_type(delimiter, 'I') || is_type(delimiter, 'R') || is_type(delimiter, 'T') || is_type(delimiter, 'H') || is_type(delimiter, 'P'))
				{
					ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
					return (258);
				}
				else
					*str_heredoc = heredoc(mini, delimiter.str);
				ft_free(tokens[i + 1].str, 1);
				tokens[i + 1].str = NULL;
			}
			else
			{
				ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
				return (258);
			}
			ft_free(tokens[i].str, 1);
			tokens[i].str = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	dup_tokens(t_mini *mini, t_token *tokens, char *str_heredoc)
{
	int	i;
	int	j;

	mini->tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	i = 0;
	if(str_heredoc && str_heredoc[0])
	{
		mini->tokens[i].str = ft_strdup("/bin/echo");
		mini->tokens[i++].type = 'A';
		mini->tokens[i].str = ft_strdup("-e");
		mini->tokens[i++].type = 'A';
		mini->tokens[i].str = str_heredoc;
		mini->tokens[i++].type = 'A';
		if(tokens[0].str)
		{
			mini->tokens[i].str = ft_strdup("|");
			mini->tokens[i++].type = 'P';
		}
		j = 0;
		while (tokens[j].str)
		{
			mini->tokens[i + j].str = ft_strdup(tokens[j].str);
			mini->tokens[i + j].type = tokens[j].type;
			j++;
		}
		mini->tokens[i + j].str = NULL;
	}
	else
	{
		i = 0;
		while (tokens[i].str)
		{
			mini->tokens[i].str = ft_strdup(tokens[i].str);
			mini->tokens[i].type = tokens[i].type;
			i++;
		}
		mini->tokens[i].str = NULL;
	}
}

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
		ft_putstr_fd("exit\n", 2);
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
	ft_free_tokens(mini->tokens);
	free_env(mini->env);
}
