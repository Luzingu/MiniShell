/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 01:03:14 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int has_unclosed_quotes(char *str, char *quote_type)
{
    int double_quotes;
    int single_quotes;
    int i;

    double_quotes = 0;
    single_quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' && single_quotes % 2 == 0)
            double_quotes++;
        else if (str[i] == '\'' && double_quotes % 2 == 0)
            single_quotes++;
        i++;
    }
    if (double_quotes % 2 != 0)
        *quote_type = '"';
    else if (single_quotes % 2 != 0)
        *quote_type = '\'';
    return (double_quotes % 2 != 0 || single_quotes % 2 != 0);
}

void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

char *read_input(void)
{
    char *readed;
    char quote_type = '\0';
    char *continuation;

    readed = readline("minishell> ");
    if (!readed)
        return (NULL);
    while (has_unclosed_quotes(readed, &quote_type))
    {
        continuation = (quote_type == '"') ? readline("dquote> ") : readline("squote> ");
        readed = ft_strcat(readed, continuation);
        if (!has_unclosed_quotes(readed, &quote_type))
            break ;
        readed = ft_strcat(readed, "\n");
    }
    return readed;
}

void setup_pipe(int *pipe_fd, int i, int num_comandos)
{
    if (i != num_comandos - 1)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
}

void handle_child_process(int *pipe_fd, int *prev_pipe_fd, int i, int num_comandos, char *cmd)
{
    char *comando;
    char *args;
    char *bin;

    get_output_fd(pipe_fd, i, num_comandos, &cmd);
    get_input_fd(prev_pipe_fd, i, &cmd);
    get_command(cmd, &comando, &args);
    if (ft_strncmp(comando, "echo", 4) == 0)
    {
        ft_echo(args, STDOUT_FILENO);
    }
    else
    {
        bin = ft_strcat("/bin/", comando);
        if (i != 0)
            close(prev_pipe_fd[1]);
        if (i != num_comandos - 1)
            close(pipe_fd[0]);
        execute_ve(bin, args, NULL);
    }
    exit(EXIT_SUCCESS);
}

void handle_parent_process(int *pipe_fd, int *prev_pipe_fd, int i, int num_comandos, pid_t pid_f)
{
    int status;

    if (i != 0)
    {
        close(prev_pipe_fd[0]);
        close(prev_pipe_fd[1]);
    }
    if (i != num_comandos - 1)
    {
        prev_pipe_fd[0] = pipe_fd[0];
        prev_pipe_fd[1] = pipe_fd[1];
    }
    waitpid(pid_f, &status, 0);
}

void process_command(char *cmd, int i, int num_comandos, int *prev_pipe_fd)
{
    int pipe_fd[2];
    pid_t pid_f;

    setup_pipe(pipe_fd, i, num_comandos);

    pid_f = fork();
    if (pid_f == 0)
        handle_child_process(pipe_fd, prev_pipe_fd, i, num_comandos, cmd);
    else if (pid_f > 0)
        handle_parent_process(pipe_fd, prev_pipe_fd, i, num_comandos, pid_f);
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    char *readed;
    char **mtx_comandos;
    int num_comandos;
    int i;
    int prev_pipe_fd[2] = {-1, -1};

    handle_signals();
    while (1)
    {
        readed = read_input();
        if (!readed)
            break;
        add_history(readed);
        mtx_comandos = ft_split_advanced(readed, "|");
        num_comandos = numb_split(mtx_comandos);
        i = 0;
        while (i < num_comandos)
        {
            process_command(mtx_comandos[i], i, num_comandos, prev_pipe_fd);
            i++;
        }
        if (num_comandos > 1)
        {
            close(prev_pipe_fd[0]);
            close(prev_pipe_fd[1]);
        }
        free(readed);
        ft_free_mtrs(mtx_comandos);
    }
    return 0;
}

