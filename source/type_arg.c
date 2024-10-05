#include "../header/minishell.h"

void	type_arg(t_token *start, t_token *token)
{
	size_t	len_str;
	t_token	*prev;

	prev = prev_sep(start, token);
	len_str = 0;
	if (token->str)
		len_str = ft_strlen(token->str);
	if (!ft_strncmp(token->str, ">", len_str))
		token->type = "trunc";
	else if (!ft_strncmp(token->str, ">>", len_str))
		token->type = "append";
	else if (!ft_strncmp(token->str, "<<", len_str))
		token->type = "heredoc";
	else if (!ft_strncmp(token->str, "<", len_str))
		token->type = "input";
	else if (!ft_strncmp(token->str, "|", len_str))
		token->type = "pipe";
	else if (prev == NULL || ft_is_type(prev, "end")
		|| ft_is_type(prev, "append")
		|| ft_is_type(prev, "input")
		|| ft_is_type(prev, "pipe"))
		token->type = "cmd";
	else
		token->type = "arg";
}
