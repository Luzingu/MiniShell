#include "../../header/minishell.h"

char **ft_unset(char *args, char ***env)
{
    int i = 0;
    int j = 0;
    char **new_env;

    // Adicione um "=" para facilitar a comparação
    char *to_remove = ft_strjoin(args, "=");

    while ((*env)[i])
        i++;

    new_env = malloc(sizeof(char *) * i); // Tamanho máximo sem a variável a ser removida
    if (!new_env)
    {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp(to_remove, (*env)[i], ft_strlen(to_remove)) != 0)
        {
            new_env[j++] = ft_strdup((*env)[i]); // Copie a variável se não for a que está sendo removida
        }
        i++;
    }
    new_env[j] = NULL;
    ft_free_matrix(*env); // Libera a memória do ambiente antigo
    free(to_remove); // Libera a memória da string temporária
    return new_env; // Retorna o novo ambiente
}

void handle_unset(char **tmp, char ***env)
{
    int n = 1;
    while (tmp[n])
    {
        *env = ft_unset(tmp[n], env); // Supomos que ft_export é segura
        n++;
    }
}