#include "../header/minishell.h"

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->prev;
	return (token);
}

t_token	*next_run(t_token *token)
{
	while (token && !ft_is_type(token, "cmd"))
	{
		token = token->next;
		if (token && ft_is_type(token, "pipe") && token->prev != NULL)
			token = token->next;
	}
	return (token);
}

int	ft_is_type(t_token *token, char *type)
{
	if (token && ft_strncmp(token->type, type, ft_strlen(type)) == 0)
		return (1);
	return (0);
}