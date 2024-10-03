#include "../header/minishell.h"

t_token	*next_sep(t_token *token)
{
	while (token && (ft_is_type(token, "arg") || ft_is_type(token, "cmd")))
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *start, t_token *current)
{
	t_token *tmp;
	t_token *prev;

	tmp = start;
	prev = NULL;
	while (tmp != NULL && tmp != current)
    {
        prev = tmp;
        tmp = tmp->next;
    }
	return (prev);
}

t_token	*next_run(t_token *token)
{
	while (token && !ft_is_type(token, "cmd"))
	{
		token = token->next;
		if (token && ft_is_type(token, "pipe")) // && token->prev != NULL
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