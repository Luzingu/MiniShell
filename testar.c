#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int my_setenv(const char *name, const char *value) {
    int i;
    size_t name_len = strlen(name);
    char *new_var = malloc(name_len + strlen(value) + 2); // "NOME=VALOR\0"
    
    if (!new_var) return -1;

    sprintf(new_var, "%s=%s", name, value);

    for (i = 0; environ[i]; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            free(environ[i]);   // Libera a antiga variável
            environ[i] = new_var; // Substitui pelo novo valor
            return 0;
        }
    }

    // Se não encontrou a variável, adicionar uma nova
    environ[i] = new_var;
    environ[i+1] = NULL; // Terminar o array com NULL
    return 0;
}

int my_unsetenv(const char *name) {
    int i, j;
    size_t name_len = strlen(name);

    for (i = 0; environ[i]; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            // Encontrou a variável, remove-a e reorganiza o array
            free(environ[i]);
            for (j = i; environ[j]; j++) {
                environ[j] = environ[j + 1]; // Desloca o resto
            }
            return 0;
        }
    }

    return -1; // Variável não encontrada
}



// Função para imprimir todas as variáveis de ambiente (comando `env`)
void print_env() {
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

// Função para definir ou modificar uma variável de ambiente (comando `export`)
void my_setenv(const char *name, const char *value) {
    if (setenv(name, value) == 0) {
        printf("Variável %s definida como %s\n", name, value);
    } else {
        perror("Erro ao definir variável de ambiente");
    }
}

// Função para remover uma variável de ambiente (comando `unset`)
void unset_env_var(const char *name) {
    if (my_unsetenv(name) == 0) {
        printf("Variável %s removida\n", name);
    } else {
        perror("Erro ao remover variável de ambiente");
    }
}

// Função para expandir variáveis de ambiente no comando

char* expand_variables(const char *input)
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

// Função para lidar com o comando `echo`
void handle_echo(char *input) {
    char *expanded_input = expand_variables(input);
    printf("%s\n", expanded_input);
    free(expanded_input);
}

// Função para lidar com o comando `export` sem opções
void print_exported_vars() {
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++) {
        printf("declare -x %s\n", environ[i]);
    }
}

int main() {
    char input[BUFFER_SIZE];
    char *expanded_input;

    while (1) {
        printf("minishell> ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';  // Remover '\n'

        // Expandir variáveis de ambiente
        expanded_input = expand_variables(input);

        // Comando `exit`
        if (strcmp(expanded_input, "exit") == 0) {
            free(expanded_input);
            break;
        }

        // Comando `env` sem opções
        else if (strcmp(expanded_input, "env") == 0) {
            print_env();
        }

        // Comando `export` sem opções (exibe todas as variáveis)
        else if (strcmp(expanded_input, "export") == 0) {
            print_exported_vars();
        }

        // Comando `export VAR=valor`
        else if (strncmp(expanded_input, "export ", 7) == 0) {
            char *name = strtok(expanded_input + 7, "=");
            char *value = strtok(NULL, "=");
            if (name && value) {
                set_env_var(name, value);
            } else {
                printf("Uso: export VAR=valor\n");
            }
        }

        // Comando `unset` sem opções
        else if (strcmp(expanded_input, "unset") == 0) {
            printf("Uso: unset VAR\n");
        }

        // Comando `unset VAR`
        else if (strncmp(expanded_input, "unset ", 6) == 0) {
            char *name = strtok(expanded_input + 6, " ");
            if (name) {
                unset_env_var(name);
            } else {
                printf("Uso: unset VAR\n");
            }
        }

        // Comando `echo`
        else if (strncmp(expanded_input, "echo ", 5) == 0) {
            handle_echo(expanded_input + 5);  // Expandir variáveis após "echo"
        }

        // Comando desconhecido
        else {
            printf("Comando não reconhecido: %s\n", expanded_input);
        }

        free(expanded_input); // Liberar memória após cada loop
    }

    return 0;
}
