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
        if (strcmp(line, delimiter) == 0)
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
    int i = 0;
    char **tokens;
    char *delimiter;

    tokens = ft_split(line, ' '); 
    while (tokens[i])
    {
        if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1] != NULL)
        {
            delimiter = tokens[i + 1];
            process_heredoc(delimiter);
            return (1);
        }
        i++;
    }
    ft_free_matrix(tokens);
    return (0);
}