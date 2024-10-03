#include "../../header/minishell.h"

t_token *get_last_token(t_token *next)
{
    t_token *last;

    last = next;
    while (last && last->next)
        last = last->next;
    return (last);
}


t_token *create_token(char *str)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->str = str;
    token->type = 0;
    token->next = NULL;
    return (token);
}

t_token *process_token(char *str, t_token **next, t_token **first_token)
{
    t_token *new;

    new = create_token(str);
    if (new)
    {
        type_arg(*first_token, new);
        if (*next)
            (*next)->next = new;
        *next = new;
        if (!(*first_token))
            *first_token = new;
    }
    return (*next);
}

void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}

t_token *process_line(char *line)
{
    int     i = 0;
    t_token *next = NULL;
    t_token *first_token = NULL;
    char    *str;

    while (line[i])
    {
        skip_whitespace(line, &i);
        str = return_str(line, &i);
        if (str && str[0])
            process_token(str, &next, &first_token);
        skip_whitespace(line, &i);
        if (is_separator(line[i]))
        {
            str = get_separator(line, &i);
            if (str && str[0])
                process_token(str, &next, &first_token);
        }
    }
    return (first_token);
}

t_token *get_tokens(char *line)
{
    t_token *tokens;

    line = ft_strtrim(line, " ");
    tokens = process_line(line);
    return tokens;
}
