/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:34:46 by aluzingu          #+#    #+#             */
/*   Updated: 2024/10/09 08:28:31 by mcaquart         ###   ########.fr       */
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
# include <dirent.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char			*str;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_env	*env_copy;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		pid;
	int		charge;
	int		parent;
	int		last_return;
	int		no_exec;
	int		exit_status;
}	t_mini;

t_token	*get_tokens(char *line);
t_token	*prev_sep(t_token *start, t_token *current);
t_env	*add_envirenoment(char *env_name, char *env_value);
t_env	*sort_env_list(t_env *head);

void	redir_and_exec(t_mini *mini, t_token *token, int pipe);
void	redir(t_mini *mini, t_token *token, char *type);
void	input(t_mini *mini, t_token *token);
void	handle_export(char **tmp, t_env **env, t_mini *mini);
void	str_dup_env(char **env, t_mini *mini);
void	ft_close(int fd);
void	ft_free_matrix(char **matrix);
void	ft_env(t_env *env);
void	ft_export(char *args, t_env **env);
void	ft_echo(char **args, t_mini *mini);
void	ft_cd(t_mini *mini, char **argument);
void	ft_exit(char **matrix, t_mini *mini);
void	execute_cmd(t_mini *mini, char **cmd);
void	increment_shell_level(t_mini *mini);
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);
void	handle_signals(void);
void	type_arg(t_token *start, t_token *token);
void	ft_unset(char *args, t_env **env);

char	*ft_verifying_line(char *line);
char	*ft_pwd(t_mini *mini);
char	*expand_variables(t_mini *mini, char *input);
char	*ft_getenv(t_env *env, char *var);
char	*get_separator(char *line, int *i);
char	*return_str(char *ptr, int *i);
char	**env_to_matrix(t_env *env, int i);
char	**ft_split_advanced(const char *s, const char *delimiter);
char	*my_strndup(const char *s, size_t n);
char	**cmd_tab(t_token *start, int i);
char	*get_env_value(t_mini *mini, char *input, int *n);
int		handle_unset(char **tmp, t_env **env);
int		minipipe(t_mini *mini);
int		ignore_sep(char *line, int i);
int		ft_is_type(t_token *token, char *type);
int		ft_strisnum(const char *str);
int		exec_builtin(char **args, t_mini *mini);
int		nb_args(char **args);
int		whereis(const char *str, const char *needle);
int		numb_split(char **matrix);
int		verifying_argument(t_mini *mini, t_token *token);
int		handle_heredoc(char *line);
int		is_separator(char c);
void	toggle_quotes(char c, char *in_single_quotes, char *in_double_quotes);
int		check_delimiter(const char *s, const char *delimiter, size_t len, size_t delimiter_len, size_t *i);
size_t	count_loop(const char *s, const char *delimiter, size_t len, size_t delimiter_len);
size_t	count_substrings(const char *s, const char *delimiter);

#endif