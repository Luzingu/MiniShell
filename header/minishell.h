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
    # include "../libft/libft.h"
	
	void	ft_echo(char *argument, int fd);
	void	ft_exit(char **matrix);
	void	ft_cat(char **argument);
    void    execute_ve(char *bin, char *argument, char **var_ambiente);
    void    ft_free_mtrs(char **matrix);
    void    get_command(char *str, char **command, char **argument);
    char    *ft_strcat(char *str1, char *str2);
    char **ft_split_advanced(const char *s, const char *delimiter);
    int numb_split (char **mtx);
    void    get_input_fd(int *prev_pipe_fd, int i, char **comando);
    void    get_output_fd(int *pipe_fd, int i, int num_comandos, char **comando);
    int whereis(const char *str, const char *needle);

#endif
