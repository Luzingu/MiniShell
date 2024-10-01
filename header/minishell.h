/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:34:46 by aluzingu          #+#    #+#             */
/*   Updated: 2024/10/01 00:49:24 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 1000000000

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
# include <sys/stat.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char			*str;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	t_token		*start;
	char		**env;
	char		**env_copy;
	int			in;
	int			out;
	int			fdin;
	int			fdout;
	int			pipin;
	int			pipout;
	int			pid;
	int			charge;
	int			parent;
	int			last_return;
	int			no_exec;
}	t_mini;

t_token	*get_tokens(char *line);

void	redir_and_exec(t_mini *mini, t_token *token);
void	redir(t_mini *mini, t_token *token, char *type);
void	input(t_mini *mini, t_token *token);
void	free_tab(char **tab);
void	ft_close(int fd);
void	handle_export(char **tmp, char ***env);
int		handle_unset(char **tmp, char ***env);
void	ft_free_matrix(char **matrix);
void	ft_env(char **env, t_mini *mini);
char	**str_dup_env(char **env);
char	*find_executable(char *cmd, char **env);
char	*ft_verifying_line(char *line);
char	**ft_export(char *args, char **env);
char	*ft_pwd(t_mini *mini);

int		get_next_line2(int fd, char **line);
int		is_types(t_token *token, char *types);
int		minipipe(t_mini *mini);
int		ignore_sep(char *line, int i);
int		ft_is_type(t_token *token, char *type);
int		ft_strisnum(const char *str);
int		is_builtin(char *command);
int		exec_builtin(char **args, t_mini *mini);
void	ft_echo(char **args, t_mini *mini);
void	ft_cd(char ***env, char **argument, t_mini *mini);
void	ft_exit(char **matrix, t_mini *mini);
int		nb_args(char **args);
int		whereis(const char *str, const char *needle);
int		numb_split(char **matrix);
char	*expand_variables(t_mini *mini, char *input);
char	*ft_getenv(char **env, char *var);
void execute_cmd(t_mini *mini, char **cmd);
int		verifying_argument(t_mini *mini, t_token *token);
int	increment_shell_level(char **env);
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);
int	handle_heredoc(char *line);
void handle_signals(void);
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_run(t_token *token);
char	*get_separator(char *line, int *i);
int is_separator(char c);
void    type_arg(t_token *token);
char	*return_str(char *ptr, int *i);
#endif