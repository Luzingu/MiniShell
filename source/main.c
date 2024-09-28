#include "../header/minishell.h"

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
    while (1)
    {
        line = readline("minishell>");
        if (!line)
            break;
        mini.in = dup(STDIN);
        mini.out = dup(STDOUT);
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