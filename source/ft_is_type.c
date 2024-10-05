#include "../header/minishell.h"

int	ft_is_type(t_token *token, char *type)
{
	return ((token && ft_strncmp(token->type, type, ft_strlen(type)) == 0));
}
