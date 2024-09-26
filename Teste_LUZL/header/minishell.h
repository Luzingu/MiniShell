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
    # include <limits.h>
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

    # define EMPTY 0
    # define CMD 1
    # define ARG 2
    # define TRUNC 3
    # define APPEND 4
    # define INPUT 5
    # define PIPE 6
    # define END 7

    # define STDIN 0
    # define STDOUT 1
    # define STDERR 2

    typedef struct s_token
    {
        char *str;
        int type;
        struct s_token *prev;
        struct s_token *next;
    } t_token;

    typedef struct	s_mini
    {
        t_token			*start;
        char			**env;
        char			**secret_env;
        int				in;
        int				out;
        int				fdin;
        int				fdout;
        int				pipin;
        int				pipout;
        int				pid;
        int				charge;
        int				parent;
        int				last;
        int				ret;
        int				exit;
        int				no_exec;
    }				t_mini;

    int		get_next_line2(int fd, char **line);
    t_token *get_tokens(char *line);
    int	ft_strcmp(const char *s1, const char *s2);
    int		is_type(t_token *token, int type);
    void	type_arg(t_token *token, int separator);
    int		is_types(t_token *token, char *types);
    void	redir_and_exec(t_mini *mini, t_token *token, char **env);
    void	redir(t_mini *mini, t_token *token, int type);
    void	input(t_mini *mini, t_token *token);
    int		minipipe(t_mini *mini);
    void	free_tab(char **tab);
    void	ft_close(int fd);
    int ignore_sep(char *line, int i);
    int		check_line(t_mini *mini, t_token *token);
#endif
