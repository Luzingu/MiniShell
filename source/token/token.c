#include "../../header/minishell.h"



t_token *create_token(char *str)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->str = str;
    token->type = 0;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}

t_token *process_token(char *str, t_token *prev)
{
    t_token *next;

	next = create_token(str);
    if (next)
    {
        next->prev = prev;
        type_arg(next);
        if (prev)
            prev->next = next;
    }
    return (next);
}

void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}

static t_token *process_line(char *line)
{
    int     i = 0;
    t_token *prev = NULL;
    char    *str;

    while (line[i])
    {
        skip_whitespace(line, &i);
        str = return_str(line, &i);
        if (str && str[0])
            prev = process_token(str, prev);
        skip_whitespace(line, &i);
        if (is_separator(line[i]))
        {
            str = get_separator(line, &i);
            if (str && str[0])
                prev = process_token(str, prev);
        }
    }
    return (prev);
}

t_token *get_tokens(char *line)
{
    t_token *tokens;
    t_token *first_token;

    line = ft_strtrim(line, " ");
    tokens = process_line(line);
    first_token = tokens;
    while (first_token && first_token->prev)
        first_token = first_token->prev;
    return (first_token);
}