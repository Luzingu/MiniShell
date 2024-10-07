#include "../header/minishell.h"

char *my_strndup(const char *s, size_t n)
{
    char *dup;
    size_t i;

    if (!s)
        return (NULL);
    dup = (char *)malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i] != '\0')
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
