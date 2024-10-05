#include "../header/minishell.h"

int	is_separator(char c)
{
	return ((c == '|' || c == '>' || c == '<'));
}
