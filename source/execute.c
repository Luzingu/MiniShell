/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:12:39 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:57:36 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int exec_command(char *command, int fd_in, int pipefd[2], char **env)
{
    pid_t pid;
    char **args;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) // Processo filho
    {
        if (fd_in != 0) {
            dup2(fd_in, 0); // Redireciona a entrada para o comando
            close(fd_in); // Fechar o descritor após duplicar
        }
        if (pipefd[1] != -1) {
            dup2(pipefd[1], 1); // Redireciona a saída para o próximo pipe
            close(pipefd[1]);   // Fecha o descritor após duplicar
        }
        
        close(pipefd[0]); // Fecha o lado de leitura do pipe

        args = (char **)malloc(sizeof(char *) * 4);
        args[0] = "/bin/sh";
        args[1] = "-c";
        args[2] = command;
        args[3] = NULL;
        execve("/bin/sh", args, env); // Executa o comando
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Processo pai fecha os pipes e espera o filho
    if (fd_in != 0) {
        close(fd_in); // Fecha o descritor de leitura anterior
    }
    if (pipefd[1] != -1) {
        close(pipefd[1]); // Fecha o descritor de escrita do pipe
    }

    wait(NULL); // Aguarda o processo filho

    return pipefd[0]; // Retorna o descritor para leitura do próximo comando
}

// Função principal para executar comandos
char *execute_commands(char **commands, char ***env)
{
    int fd_in = 0;
    int pipefd[2];
    char **tmp;
    int i = 0;

    while (commands[i])
    {
        commands[i] = ft_strtrim(commands[i], " ");
        tmp = ft_split_advanced(commands[i], "<<");
        if (tmp[1]) // Heredoc
        {
            fd_in = read_heredoc(tmp[1]);
            ft_free_mtrs(tmp);
            i++;
            continue;
        }
        ft_free_mtrs(tmp);
        tmp = ft_split_advanced(commands[i], " ");

        if (ft_strncmp(tmp[0], "exit", ft_strlen(tmp[0])) == 0)
        {
            ft_exit(tmp);
            i++;
            continue;
        }
        
        if (ft_strncmp(tmp[0], "cd", ft_strlen(tmp[0])) == 0)
        {
            ft_cd(env, tmp);
            i++;
            continue;
        }

        if (ft_strncmp(tmp[0], "unset", 5) == 0)
        {
            if (tmp[1])
                handle_unset(tmp, env);
            i++;
            continue;
        }
        if (ft_strncmp(tmp[0], "export", 6) == 0 && tmp[1])
        {
            handle_export(tmp, env);
            ft_free_mtrs(tmp);
            i++;
            continue;
        }
        if (!find_executable(tmp[0], *env))
        {
            printf("Nao existe nenhum executavel encontrado. \n");
            i++;
            continue;
        }
        else if (ft_strncmp(tmp[0], "env", 3) == 0 && tmp[1])
        {
            i++;
            continue;
        }

        if (commands[i + 1])
        {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                ft_free_mtrs(tmp);
                return NULL;
            }
        } 
        else
        {
            pipefd[0] = -1;
            pipefd[1] = -1;
        }

        fd_in = exec_command(commands[i], fd_in, pipefd, *env);
        if (fd_in == -1) {
            //ft_free_mtrs(tmp);
            return NULL;
        }

        //ft_free_mtrs(tmp);
        i++;
    }

    return NULL;
}