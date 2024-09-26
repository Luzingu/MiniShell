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

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
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
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
    reset_fds(&mini);
    while (1)
    {
        line = readline("minishell>");
        if (!line)
            break;
        mini.start = get_tokens(line);
        token = next_run(mini.start, 0);
        if (check_line(&mini, token))
        {
            token = (is_types(mini.start, "TAI")) ? mini.start->next : token;
            while (token)
            {
                mini.charge = 1;
                mini.parent = 1;
                mini.last = 1;
                redir_and_exec(&mini, token, env);
                reset_std(&mini);
                close_fds(&mini);
                reset_fds(&mini);
                waitpid(-1, &status, 0);
                mini.ret = (mini.last == 0) ? status : mini.ret;
                if (mini.parent == 0)
                {
                    free(mini.start);
                    exit(mini.ret);
                }
                mini.no_exec = 0;
                token = next_run(token, 1);
            }
        }
    }
    

    return (0);
}