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
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char			*str;
	char			*type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	int				equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_values
{
	int		val1;
	int		val2;
	char	*str1;
	char	*str2;
}	t_values;

typedef struct s_mini
{
	char		**tokens;
	t_env		*env;
	t_env		*env_copy;
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
	int			exit_status;
	t_values	values;
}	t_mini;

typedef struct s_state
{
	char	in_single_quotes;
	char	in_double_quotes;
	size_t	delimiter_len;
	size_t	i;
	size_t	start;
	size_t	len;
}	t_state;

char	**get_tokens(t_mini *mini, char *line);
t_token	*prev_sep(t_token *start, t_token *current);
t_env	*add_envirenoment(char *env_name, char *env_value, int equal);
t_env	*sort_env_list(t_env *head);

void	sigint_handler(int sig);
void	redir_and_exec(t_mini *mini, int pos_token, int pipe);
void	redir(t_mini *mini, char *file, char *type);
void	input(t_mini *mini, char *file);
void	handle_export(char **tmp, t_env **env, t_mini *mini);
void	str_dup_env(char **env, t_mini *mini, int equal);
void	ft_close(int fd);
void	ft_free_matrix(char **matrix);
void	ft_env(t_env *env, int type);
void	ft_export(char *args, t_env **env, int equal, int new_env);
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
void	ft_free_all(t_mini *mini);
void	ft_free(void *ptr, int free_ptr);
void	free_tokens(t_token *head);
void	main_loop(t_mini *mini);
void	free_env(t_env *head);
void	toggle_quotes(char c, t_state *state);

char	*ft_pwd(t_mini *mini);
char	*expand_variables(t_mini *mini, char *input, int in_heredoc);
char	*ft_getenv(t_env *env, char *var);
char	*get_separator(char *line, int *i);
char	*return_str(char *ptr, int *i);
char	**env_to_matrix(t_env *env, int i, int type);
char	**ft_split_advanced(const char *s, const char *delimiter);
char	*my_strndup(const char *s, size_t n);
char	**cmd_tab(char **tokens, int *pos_token);
char	*get_env_value(t_mini *mini, char *input, int *n);
char	**allocate_result(size_t count);
char	**process_str(t_mini *mini, char *line);
char	**heredoc(t_mini *mini, const char *delimiter, int count);
char	*ft_strjoin2(char *s1, char *s2, int free_s1, int free_s2);
int		handle_unset(char **tmp, t_env **env);
int		minipipe(t_mini *mini);
int		ignore_sep(char *line, int i);
int		ft_is_type(t_token *token, char *type);
int		ft_strisnum(const char *str);
int		exec_builtin(char **args, t_mini *mini);
int		nb_args(char **args);
int		whereis(const char *str, const char *needle);
int		numb_split(char **matrix);
int		verifying_argument(t_mini *mini, char **matrix);
int		handle_heredoc(t_mini *mini, char *line);
int		is_separator(char c);
int		check_delimiter(const char *s, const char *delimiter,
			t_state *state, size_t delimiter_len);
size_t	count_loop(const char *s, const char *delimiter,
			t_state *state, size_t delimiter_len);
size_t	count_substrings(const char *s, const char *delimiter);
int		ft_strcmp(const char *s1, const char *s2);
int		get_variable_length(t_mini *mini, char *input, int *n);
int		handle_return_value(t_mini *mini, int *n, int *len_aloc);
int		ft_can_be_add(char *str, int i, t_mini *mini);
int		ft_is_closed(char *str, int i, char quote);
int		ft_is_unclosed_quote(char *str, int i, char quote, t_mini *mini);
int		is_separator_str(char *str);
#endif
