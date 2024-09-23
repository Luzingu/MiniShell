#include "../header/minishell.h"

int has_unclosed_quotes(char *str, char *quote_type)
{
    int double_quotes;
    int single_quotes;
    int i;

    double_quotes = 0;
    single_quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' && single_quotes % 2 == 0)
            double_quotes++;
        else if (str[i] == '\'' && double_quotes % 2 == 0)
            single_quotes++;
        i++;
    }
    if (double_quotes % 2 != 0)
        *quote_type = '"';
    else if (single_quotes % 2 != 0)
        *quote_type = '\'';
    return (double_quotes % 2 != 0 || single_quotes % 2 != 0);
}
char *read_input(void)
{
    char *readed;
    char quote_type = '\0';
    char *continuation;

    readed = readline("minishell> ");
    if (!readed)
        return NULL;
    while (has_unclosed_quotes(readed, &quote_type))
    {
    	if (quote_type == '"')
        	continuation = readline("dquote> ");
    	else
    		continuation = readline("squote> ");
        readed = ft_strjoin(readed, continuation);
        if (!has_unclosed_quotes(readed, &quote_type))
            break;
        readed = ft_strjoin(readed, "\n");
    }
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