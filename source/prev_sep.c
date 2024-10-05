#include "../header/minishell.h"

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
