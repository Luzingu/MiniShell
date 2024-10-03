#include "../../header/minishell.h"

char *concat_key_value(t_env *env)
{
    if (!env || !env->key || !env->value) // Verificar se os campos são válidos
        return NULL;

    int len = strlen(env->key) + strlen(env->value) + 2; // +2 para '=' e '\0'
    char *key_value = malloc(len);
    if (!key_value)
        return NULL;

    snprintf(key_value, len, "%s=%s", env->key, env->value);
    return key_value;
}

int compare_env_vars(t_env *a, t_env *b)
{
    char *a_str = concat_key_value(a);
    char *b_str = concat_key_value(b);

    if (!a_str || !b_str)
    {
        free(a_str);  // Libere se alocação ocorreu antes de erro
        free(b_str);  // Libere se alocação ocorreu antes de erro
        return 0; // Caso uma das strings não possa ser criada, consideramos igual
    }

    int result = strcmp(a_str, b_str);
    free(a_str);
    free(b_str);
    return result;
}

t_env *sorted_insert(t_env *sorted, t_env *new_node)
{
    if (!new_node) // Se o novo nó for inválido, retornar a lista sem alterações
        return sorted;

    if (!sorted || compare_env_vars(new_node, sorted) < 0)
    {
        new_node->next = sorted;
        return new_node;
    }

    t_env *current = sorted;
    while (current->next && compare_env_vars(new_node, current->next) >= 0)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    return sorted;
}

t_env *sort_env_list(t_env *head)
{
    if (!head) // Se a lista estiver vazia, não há nada para ordenar
        return NULL;

    t_env *sorted = NULL;
    t_env *current = head;

    while (current)
    {
        t_env *next = current->next;
        current->next = NULL;  // Desconectar o nó atual da lista original
        sorted = sorted_insert(sorted, current);
        current = next;
    }

    return sorted;
}

// Funções auxiliares para criar e liberar a lista, para facilitar os testes
t_env *create_node(char *key, char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node) return NULL;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    return new_node;
}