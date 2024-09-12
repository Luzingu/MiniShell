/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/12 13:32:59 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int numb_split (char **mtx)
{
    int num;

    num = 0;
    while (mtx[num])
        num++;
    return (num);
}

int whereis(const char *str, const char *needle)
{
    size_t i = 0;
    size_t j;
    size_t str_len = 0;
    size_t needle_len = 0;

    while (str[str_len] != '\0')
        str_len++;
    while (needle[needle_len] != '\0')
        needle_len++;
    while (i <= str_len - needle_len)
    {
        j = 0;
        while (j < needle_len && str[i + j] == needle[j])
            j++;
        if (j == needle_len)
            return (int)i;
        i++;
    }
    return (-1);
}


void heredoc(const char *delimiter, int *fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    size_t delimiter_len = ft_strlen(delimiter);

    if (pipe(fd) == -1)
    {
        perror("Erro ao criar o pipe");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            perror("Erro ao ler a linha");
            break;
        }
        buffer[bytes_read] = '\0';
        if (buffer[bytes_read - 1] == '\n')
        {
            buffer[bytes_read - 1] = '\0';
            bytes_read--;
        }
        if (ft_strncmp(buffer, delimiter, delimiter_len) == 0 && buffer[delimiter_len] == '\0')
            break;
        write(fd[1], buffer, bytes_read);
        write(fd[1], "\n", 1);
    }
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
}


void    get_input_output_fd(int *input_fd, int *output_fd, int *pipe_fd, int i, int num_comandos, char **comando)
{
    char *file;
    char **mtx_comandos;
    int w_is;
    char redirections[4][3];
    int n;
    int heredoc_fd[2];

    ft_strlcpy(redirections[0], ">>", 3);
    ft_strlcpy(redirections[1], "<<", 3);
    ft_strlcpy(redirections[2], ">", 2);
    ft_strlcpy(redirections[3], "<", 2);
    n = 0;
    while (n <= 3)
    {
        mtx_comandos = ft_split_advanced(*comando, redirections[n]);
        if (mtx_comandos[1])
        {
            file = ft_strtrim(mtx_comandos[1], " ");
            if (ft_strncmp(redirections[n], ">>", 2) == 0)
                *output_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
            else if (ft_strncmp(redirections[n], ">", 1) == 0)
                *output_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
            else if (ft_strncmp(redirections[n], "<<", 2) == 0)
            {
                heredoc(file, heredoc_fd);
                *input_fd = heredoc_fd[0];
            }
            else if (ft_strncmp(redirections[n], "<", 1) == 0)
                *input_fd = open(file, O_RDONLY);
            w_is = whereis(*comando, redirections[n]);
            (*comando)[w_is] = '\0';
            break;
        }
        n++;
    }
    if (i == 0)
    {
        if (num_comandos > 1)
        {
            *output_fd = pipe_fd[1];
            close(pipe_fd[1]);
        }
    }
    else if (i == num_comandos - 1)
    {
        *input_fd = pipe_fd[1];
        close(pipe_fd[1]);
    }
    ft_free_mtrs(mtx_comandos);
}

int main(void)
{
    char *readed;

    char *comando;
    char *args;
    char *bin;

    int input_fd;
    int out_put_fd;

    pid_t	pid_f;
    int		status;

    int num_comandos;
    char **mtx_comandos;
    int i;
    int pipe_fd[2];
    
    while (1)
    {
        readed = readline("minishell> ");
        if (!readed)
            break;
        mtx_comandos = ft_split_advanced(readed, "|");
        num_comandos = numb_split(mtx_comandos);
        input_fd = STDIN_FILENO;
        out_put_fd = STDOUT_FILENO;
        i = 0;
        while (i < num_comandos)
        {
            if (i != num_comandos - 1)
                pipe(pipe_fd);
            get_input_output_fd(&input_fd, &out_put_fd, pipe_fd, i, num_comandos, &mtx_comandos[i]);
            get_command(mtx_comandos[i], &comando, &args);
            if (ft_strncmp(comando, "echo", 4) == 0)
                ft_echo(args, out_put_fd);
            else
            {
                bin = ft_strcat("/bin/", comando);   
                pid_f = fork();
                if (pid_f == 0)
                {
                    execute_ve(bin, args, NULL, input_fd, out_put_fd);
                }
                else
                {
                    waitpid(pid_f, &status, 0);
                }
            }
            i++;
        }
        free(readed);
    }
    ft_free_mtrs(mtx_comandos);
    return (0);
}