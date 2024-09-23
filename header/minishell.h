/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:34:46 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/14 00:31:28 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
    
    # include <unistd.h>
    # include <stdio.h>
    # include <stdlib.h>
    # include <string.h>
    # include <fcntl.h>
    # include <errno.h>
    # include <sys/wait.h>
    # include <readline/readline.h>
    # include <readline/history.h>
    # include <signal.h>
    # include <termios.h>
    #include <sys/stat.h>
    # include "../libft/libft.h"
	
    void    ft_free_mtrs(char **matrix);
    char **ft_split_advanced(const char *s, const char *delimiter);
    int numb_split (char **mtx);
    void    get_input_fd(int *prev_pipe_fd, int i, char **comando);
    void    get_output_fd(int *pipe_fd, int i, int num_comandos, char **comando);
    int whereis(const char *str, const char *needle);
    char *read_input(void);
    int read_heredoc(const char *delimiter);
    char *execute_commands(char **commands, char ***env);
    char *find_executable(char *cmd, char **env);
    void handle_unset(char **tmp, char ***env);
    void handle_export(char **tmp, char ***env);
    char *my_strndup(const char *s, size_t n);
    void    ft_exit(char **matrix);
    void    ft_cd(char ***env, char **argument);
    char *my_getenv(char **env, const char *name);
    char **ft_export(char *args, char **env);

#endif
