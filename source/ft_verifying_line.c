#include "../header/minishell.h"

int ft_check_quotes(char *str)
{
	int i = -1;
	int n_quote = 0;
	char quote_check;

	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_check = str[i];
			break;
		}
	}
	i = -1;
	while (str[++i])
		if (str[i] == quote_check)
			n_quote++;
	return (n_quote % 2 == 0);
}

char get_quote_check(char *str)
{
	int i = 0;
	char quote_check;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_check = str[i];
			return (quote_check);
		}
		i++;
	}
	return (0);
}

char *ft_verifying_line(char *line)
{
    char **matrix;
    char *new_line;
    char quote_check;
    int i = 0;
    int j = 0;
    int line_length = 0;

    matrix = ft_split(line, ' ');
    while (matrix[i])
    {
        if (!ft_check_quotes(matrix[i]))
            return (NULL);
        i++;
    }
    i = 0;
    line_length = 0;
    while (matrix[i])
    {
        quote_check = get_quote_check(matrix[i]);
        j = 0;
        while (matrix[i][j])
        {
            if (matrix[i][j] != quote_check)
                line_length++;
            j++;
        }
        i++;
    }
    new_line = malloc(sizeof(char) * line_length + numb_split(matrix));
    i = 0;
    line_length = 0;
    while (matrix[i])
    {
        quote_check = get_quote_check(matrix[i]);
        j = 0;
        while (matrix[i][j])
        {
            if (matrix[i][j] != quote_check)
            {
                new_line[line_length] = matrix[i][j];
                line_length++;
            }
            j++;
        }
        if (matrix[i + 1])
        {
            new_line[line_length] = ' ';
            line_length++;
        }
        i++;
    }
    new_line[line_length] = '\0';
    ft_free_mtrs(matrix);
    free(line);
    return (new_line);
}