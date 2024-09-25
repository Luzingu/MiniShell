#include "../../header/minishell.h"

/*void	ft_echo(char **argument, int fd)
{
	int	i;
	int quote_open;
	int	put_break;
	int n;

	i = 1;
	if(ft_strncmp("-n", argument[1], ft_strlen(argument[1])) == 0)
		i = 2;
	put_break = i;
	quote_open = 0;


	
	while (i < numb_split(argument))
	{
		n = 0;	
		if ((argument[i][0] == 34 || argument[i][0] == 39) && i == 1)
		{
			quote_open = argument[i][0];
			n++;
		}
		while (argument[i][n])
		{
			if (argument[i][n] == quote_open)
			{
				quote_open = 0;
				n++;
				continue;
			}
			ft_putchar_fd(argument[i][n], fd);
			n++;
		}
		i++;
	}
	if(put_break == 1)
		ft_putchar_fd('\n', fd);
}*/

void ft_echo(char **args, int fd) {
    int i, new_line = 1;
    char *delimiter = NULL;

    for (i = 1; args[i]; ++i) {
        if (!strcmp(args[i], "-n")) new_line = 0;
        else if (!strcmp(args[i], "<")) {
            dup2(open(args[++i], O_RDONLY), STDIN_FILENO);
        } else if (!strcmp(args[i], ">")) {
            dup2(open(args[++i], O_WRONLY | O_CREAT | O_TRUNC), STDOUT_FILENO);
        } else if (!strcmp(args[i], ">>")) {
            dup2(open(args[++i], O_WRONLY | O_CREAT | O_APPEND), STDOUT_FILENO);
        } else if (!strcmp(args[i], "<<")) {
            delimiter = args[++i];
            while ((args[++i]) && strcmp(args[i], delimiter));
        } else {
            printf("%s ", args[i]);
        }
    }
    if (new_line)
    	ft_putchar_fd('\n', fd);
}