#include "../header/minishell.h"

char *read_input(void)
{
    char *readed;

    readed = readline("minishell> ");
    if (!readed)
        return NULL;
    return (readed);
}

int read_heredoc(const char *delimiter)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;  // Retorna -1 em caso de erro
    }

    while (1) {
        ft_putstr_fd("> ", STDIN_FILENO);
        read = getline(&line, &len, stdin);
        if (read == -1) {
            perror("getline");
            break;
        }

        // Removendo o newline para comparar com o delimitador
        line[strcspn(line, "\n")] = 0;

        // Se o input for igual ao delimitador, termina o loop
        if (strcmp(ft_strtrim(line, " "), delimiter) == 0)
            break;
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);  // Adiciona a nova linha que foi removida
    }
    
    // Fechar a escrita do pipe
    close(pipefd[1]);
    free(line);

    return pipefd[0];  // Retorna o descritor de leitura do pipe
}