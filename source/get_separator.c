#include "../header/minishell.h"

char	*get_separator(char *line, int *i)
{
	int		total_of_strings;
	char	*str;

	total_of_strings = 1;
	if (line[*i] == '>' && line[*i + 1] == '>')
		total_of_strings = 2;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		total_of_strings = 2;
	str = (char *)malloc(sizeof(char) * (total_of_strings + 1));
	if (!str)
		return (NULL);
	str[0] = line[*i];
	if (total_of_strings == 2)
		str[1] = line[*i + 1];
	str[total_of_strings] = '\0';
	*i += total_of_strings;
	return (str);
}
