#include "../../header/minishell.h"

int	ft_echo(char **argument)
{
	int	i;
	int	put_break;
	int n;

	i = 1;
	if(argument[1] && ft_strncmp("-n", argument[1], ft_strlen(argument[1])) == 0)
		i = 2;
	put_break = i;
	while (i < numb_split(argument))
	{
		n = 0;
		while (argument[i][n])
		{
			ft_putchar_fd(argument[i][n], STDOUT_FILENO);
			n++;
		}
		if (argument[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if(put_break == 1)
		ft_putchar_fd('\n', 1);
	return (1);
}