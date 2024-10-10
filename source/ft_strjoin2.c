#include "../header/minishell.h"

char	*ft_strjoin2(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*result;
	int		i;
	int		j;
	size_t	total_len;

	if (!s1 || !s2)
    {
        ft_free(s1, free_s1);
        ft_free(s2, free_s2);
        return (NULL);
    }
	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc((total_len * sizeof(char)) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = ((unsigned char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		result[i++] = ((unsigned char *)s2)[j++];
	result[i] = '\0';
    ft_free(s1, free_s1);
    ft_free(s2, free_s2);
	return (result);
}

