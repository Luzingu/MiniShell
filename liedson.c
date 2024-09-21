#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int whereis(const char *str, const char *needle)
{
    size_t i = 0;
    size_t j;

    while (i <= (strlen(str) - strlen(needle)))
    {
        j = 0;
        while ((j < strlen(needle)) && (str[i + j] == needle[j]))
            j++;
        if (j == strlen(needle))
            return (i);
        i++;
    }
    return (-1);
}

char    *ft_substr(const char *s, unsigned int start, size_t len)
{
    char    *str;
    char    *src;

    src = (char *)s;
    if (!src)
        return (NULL);
    if (start >= strlen(s))
    {
        str = (char *)malloc(sizeof(char));
        if (!str)
            return (NULL);
        *str = '\0';
    }
    else
    {
        if ((strlen(s) - start) < len)
            len = strlen(s) - start;
        str = (char *)malloc((sizeof(char) * len) + 1);
        if (!str)
            return (NULL);
        strlcpy(str, (char *)(s + start), len + 1);
    }
    return (str);
}

char    *ft_strcat(char *str1, char *str2)
{
    int i;
    int n;
    char    *str;

    i = strlen(str1) + strlen(str1);
    str = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    n = 0;
    while (str1[n])
        str[i++] = str1[n++];
    n = 0;
    while (str2[n])
        str[i++] = str2[n++];
    str[i] = '\0';
    return (str);
}

char    *ft_strdup(const char *s1)
{
    char    *s2;
    size_t  len;

    len = strlen(s1);
    s2 = (char *)malloc(len + 1);
    if ((s2) == NULL)
        return (NULL);
    memcpy(s2, s1, len + 1);
    return (s2);
}

void ft_export(char *args, char ***env)
{
    char *name_v;
    char *value;
    int i;
    char **new_env;
    int exist = 0;
    char *str;

    i = whereis(args, "=");
    if (i == -1)
    {
        printf("Erro: '=' não encontrado no argumento.\n");
        return;
    }

    name_v = ft_substr(args, 0, i);
    value = ft_substr(args, i + 1, strlen(args) - i - 1);
    str = malloc(strlen(name_v) + strlen(value) + 2);
    if (!str)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }
    strcpy(str, name_v);
    strcat(str, "=");
    strcat(str, value);

    i = 0;
    while ((*env)[i])
    {
        if (strncmp(name_v, (*env)[i], strlen(name_v)) == 0 && (*env)[i][strlen(name_v)] == '=')
        {
            free((*env)[i]);
            (*env)[i] = ft_strdup(str);
            exist = 1;
            break;
        }
        i++;
    }

    if (!exist)
    {
        new_env = (char **)malloc(sizeof(char *) * (i + 2));
        if (!new_env)
        {
            printf("Erro ao alocar memória.\n");
            return;
        }
        i = 0;
        while ((*env)[i])
        {
            new_env[i] = ft_strdup((*env)[i]);
            i++;
        }
        new_env[i++] = ft_strdup(str);
        new_env[i] = NULL;

        i = 0;
        while ((*env)[i])
        {
            free((*env)[i]);
            i++;
        }
        free(*env);
        *env = new_env;
    }

    free(name_v);
    free(value);
    free(str);
}


int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char **my_env;

    int i  = 0;
    while (env[i])
        i++;
    my_env = (char **)malloc(sizeof(char *) * (i+1));
    i = 0;
    while (env[i])
    {
        my_env[i] = strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    char *export = "PATH=A";
    ft_export(export, &my_env);

    i = 0;
    while (my_env[i]) {
        printf("%s\n", my_env[i]); // Imprime as variáveis de ambiente
        i++;
    }

    return 0;
}