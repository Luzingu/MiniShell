#include "../../header/minishell.h"

char *expand_variables(const char *input)
{
    char *expanded = malloc(BUFFER_SIZE);
    if (!expanded) {
        perror("Erro de memória");
        exit(EXIT_FAILURE);
    }
    expanded[0] = '\0'; 
    const char *ptr = input;
    while (*ptr) {
        if (*ptr == '$')
        {
            char var_name[BUFFER_SIZE] = {0};
            int i = 0;
            ptr++;
            while (*ptr && (isalnum(*ptr) || *ptr == '_')) {
                var_name[i++] = *ptr++;
            }
            var_name[i] = '\0';
            char *var_value = getenv(var_name);
            if (var_value)
            {
                strcat(expanded, var_value);
            }
        }
        else
        {
            strncat(expanded, ptr, 1);
            ptr++;
        }
    }
    return (expanded);
}