#include "../header/minishell.h"

int		verifying_argument(t_mini *mini, t_token *token)
{
	t_token	*prev;
	while (token)
	{
		if (ft_is_type(token, "trunc") || ft_is_type(token, "append") || ft_is_type(token, "input"))
		{
			if (!token->next || (ft_is_type(token->next, "trunc") || ft_is_type(token->next, "append") || ft_is_type(token->next, "input") || ft_is_type(token->next, "pipe")))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if (token->next)
					ft_putstr_fd(token->next->str, 2);
				else
					ft_putstr_fd("newline", 2);
				ft_putendl_fd("'", 2);
				mini->last_return = 258;
				return (0);
			}
		}
		if (ft_is_type(token, "pipe"))
		{
			prev = prev_sep(mini->start, token);
			if (!token->next || !prev || ft_is_type(prev, "trunc") || ft_is_type(prev, "append") || ft_is_type(prev, "input") || ft_is_type(prev, "pipe"))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(token->str, 2);
				ft_putstr_fd("'", 2);
				mini->last_return = 258;
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}