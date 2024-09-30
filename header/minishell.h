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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_token
{
    char *str;
    char *type;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct	s_mini
{
    t_token			*start;
    char			**env;
    char			**env_copy;
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
int	 is_types(t_token *token, char *types);
void	redir_and_exec(t_mini *mini, t_token *token);
void	redir(t_mini *mini, t_token *token, char *type);
void	input(t_mini *mini, t_token *token);
int		minipipe(t_mini *mini);
void	free_tab(char **tab);
void	ft_close(int fd);
int ignore_sep(char *line, int i);
int	ft_is_type(t_token *token, char *type);
int	ft_strisnum(const char *str);
char **str_dup_env(char **env);
char *my_getenv(char **env, char *name);
char *find_executable(char *cmd, char **env);
int	 is_builtin(char *command);
int	exec_builtin(char **args, t_mini *mini);
int	ft_echo(char **args);
void handle_export(char **tmp, char ***env);
char **ft_unset(char *args, char ***env);
int		nb_args(char **args);
void ft_free_mtrs(char **matriz);
int whereis(const char *str, const char *needle);
int numb_split (char **mtx);
char *ft_verifying_line(char *line);
char **ft_export(char *args, char **env);
int	ft_cd(char ***env, char **argument);
int	ft_exit(char **matrix);
char *ft_pwd(void);
#endif