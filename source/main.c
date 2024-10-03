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

static void process_line(t_mini *mini, char *line)
{
    t_token *token;
    int heredoc;

    heredoc = handle_heredoc(line);
    if (heredoc == 2)
    {
        mini->last_return = 258;
        printf("minishell: syntax error near unexpected token\n");
        return;
    }
    else if (heredoc == 1)
        return;
    line = ft_verifying_line(line);
    if (!line)
    {
        mini->last_return = 258;
        printf("minishell: error quotes\n");
        return;
    }
    line = expand_variables(mini, line);
    mini->start = get_tokens(line);    
    token = next_run(mini->start);    
    if (!verifying_argument(mini, token))
    {
        mini->last_return = 258;
        return;
    }
    mini->charge = 1;
    redir_and_exec(mini, token);
}

void init_mini(t_mini *mini)
{
    char *line;
    int status;

    while (mini->exit_status == 0)
    {
        mini->in = dup(STDIN_FILENO);
        mini->out = dup(STDOUT_FILENO);
        line = readline("minishell> ");
        if (!line)
        {
            mini->exit_status = 1;
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        process_line(mini, line);
        reset_std(mini);
        close_fds(mini);
        reset_fds(mini);
        waitpid(-1, &status, 0);
        mini->no_exec = 0;
        free(line);
    }
}

int main(int ac, char **argv, char **env)
{
    t_mini mini;

    (void)ac;
    (void)argv;
    reset_fds(&mini);
    str_dup_env(env, &mini);
    increment_shell_level(&mini);
    mini.last_return = 0;
    mini.exit_status = 0;
    handle_signals();
    init_mini(&mini);
    return (0);
}