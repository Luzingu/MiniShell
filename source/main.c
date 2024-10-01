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

    if (handle_heredoc(line))
    {
        free(line);
        return;
    }
    line = ft_verifying_line(line);
    if (!line)
    {
        printf("minishell: error quotes\n");
        return;
    }
    line = expand_variables(mini, line);
    mini->start = get_tokens(line);
    token = next_run(mini->start);
    if (!verifying_argument(mini, token))
    {
        free(line);
        return;
    }
    mini->charge = 1;
    redir_and_exec(mini, token);
}

void init_mini(t_mini *mini)
{
    char *line;
    int status;

    while (1)
    {
        mini->in = dup(STDIN_FILENO);
        mini->out = dup(STDOUT_FILENO);
        line = readline("minishell> ");
        if (!line)
        {
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
    int shell_level;

    (void)ac;
    (void)argv;
    reset_fds(&mini);
    mini.env = str_dup_env(env);
    mini.env_copy = str_dup_env(env);
    shell_level = increment_shell_level(mini.env);
    mini.env = ft_export(ft_strjoin("SHLVL=", ft_itoa(shell_level)), mini.env);
    mini.last_return = 0;
    handle_signals();
    init_mini(&mini);
    return (0);
}