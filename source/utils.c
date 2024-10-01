#include "../header/minishell.h"


int numb_split (char **matrix)
{
    int num;

    num = 0;
    while (matrix[num])
        num++;
    return (num);
}



int whereis(const char *str, const char *needle)
{
    size_t i = 0;
    size_t j;

    while (i <= (ft_strlen(str) - ft_strlen(needle)))
    {
        j = 0;
        while ((j < ft_strlen(needle)) && (str[i + j] == needle[j]))
            j++;
        if (j == ft_strlen(needle))
            return (int)i;
        i++;
    }
    return (-1);
}

char **str_dup_env(char **env)
{
    int i;
	char **my_env;

	i = 0;
    while (env[i])
        i++;
    my_env = (char **)malloc(sizeof(char *) * (i+1));
    i = 0;
    while (env[i])
    {
        my_env[i] = ft_strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    return (my_env);
}

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

