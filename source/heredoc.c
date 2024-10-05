#include "../header/minishell.h"

char **heredoc(const char *delimiter) 
{
    char **lines;
    int count;
    char *line;

    lines = malloc(BUFFER_SIZE * sizeof(char *));
    if (!lines)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    count = 0;
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_free_matrix(lines);
            return (NULL);
        }
        line = ft_strtrim(line, " ");
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        lines[count++] = line;
    }
    lines[count] = NULL;
    return (lines);
}

void process_heredoc(const char *delimiter)
{
    char **lines;
    int i;

    i = 0;
    lines = heredoc(delimiter);
    
    if (lines)
    {
        while (lines[i])
        {
            ft_putstr_fd(lines[i], 1);
            write(1, "\n", 1);
            i++;
        }
        ft_free_matrix(lines);
    }
}

int handle_heredoc(char *line)
{
    char **tokens;
    char **tokens2;
    char *delimiter;

    tokens = ft_split_advanced(line, "<<");
    if (tokens[1])
    {
        tokens2 = ft_split(tokens[1], ' ');
        delimiter = tokens2[0];
        if (ft_strncmp(delimiter, ">", 1) == 0 || ft_strncmp(delimiter, "<", 1) == 0 || ft_strncmp(delimiter, ">>", 2) == 0 || ft_strncmp(delimiter, "<<", 2) == 0 || ft_strncmp(delimiter, "|", 1) == 0)
            return (2);
        process_heredoc(delimiter);
        ft_free_matrix(tokens);
        return (1);
    }
    ft_free_matrix(tokens);
    return (0);
}