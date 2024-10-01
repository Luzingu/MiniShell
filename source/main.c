/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:31:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:20:31 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"


char **heredoc(const char *delimiter) 
{
    char **lines;
    int count;
    char *line;

    lines = malloc(BUFFER_SIZE * sizeof(char *));
    if (!lines)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    count = 0;
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_free_matrix(lines);
            return (NULL);
        }
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        lines[count++] = line;
    }
    lines[count] = NULL;
    return lines;
}

void process_heredoc(const char *delimiter) {
    char **lines;
    int i;

    i = 0;
    lines = heredoc(delimiter);
    
    if (lines)
    {
        while (lines[i])
        {
            ft_putstr_fd(lines[i], 1);
            write(1, "\n", 1);
            i++;
        }
        ft_free_matrix(lines);
    }
}

void handle_heredoc(char *line)
{
    int i = 0;
    char **tokens;
    char *delimiter;

    tokens = ft_split(line, ' '); 
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1] != NULL) {
            delimiter = tokens[i + 1];
            process_heredoc(delimiter);
            break;
        }
        i++;
    }
    ft_free_matrix(tokens);
}

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}



void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

t_token	*next_run(t_token *token)
{
	while (token && !ft_is_type(token, "cmd"))
	{
		token = token->next;
		if (token && ft_is_type(token, "pipe") && token->prev != NULL)
			token = token->next;
	}
	return (token);
}

int main(int ac, char **argv, char **env)
{
    t_mini mini;
    t_token	*token;
    (void)ac;
    (void)argv;
    int status;
    char *line = NULL;
    reset_fds(&mini);
   
    mini.env = str_dup_env(env);
    mini.env_copy = str_dup_env(env);
    handle_signals();
    while (1)
    {
        mini.in = dup(STDIN);
        mini.out = dup(STDOUT);
        line = readline("minishell> ");
        add_history(line);
        if (!line)
            break;
        handle_heredoc(line);
        line = ft_verifying_line(line);
        if (!line)
        {
            printf("minishell: error quotes\n");
            continue;
        }
        line = expand_variables(&mini, line);
        mini.exit = 0;
        mini.ret = 0;
        mini.no_exec = 0;
        mini.start = get_tokens(line);
        token = next_run(mini.start); 
        mini.charge = 1; 
        redir_and_exec(&mini, token);
        
        reset_std(&mini);
        close_fds(&mini);
        reset_fds(&mini);
        waitpid(-1, &status, 0);
        mini.no_exec = 0;
    }
    return (0);
}