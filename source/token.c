#include "../header/minishell.h"

int is_separator(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
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
    token->prev = NULL;
    return (token);
}

void    type_arg(t_token *token)
{
   
    size_t len_str;

    len_str = 0;
    if(token->str)
        len_str = ft_strlen(token->str);
    if (!ft_strncmp(token->str, ">", len_str))
        token->type = "trunc";
    else if (!ft_strncmp(token->str, ">>", len_str))
        token->type = "append";
    else if (!ft_strncmp(token->str, "<", len_str))
        token->type = "input";
    else if (!ft_strncmp(token->str, "|", len_str))
        token->type = "pipe";
    else if (token->prev == NULL || ft_is_type(token->prev, "end") || ft_is_type(token->prev, "append") || ft_is_type(token->prev, "input") || ft_is_type(token->prev, "pipe"))
        token->type = "cmd";
    else
        token->type = "arg";
}

char *return_str(char *ptr, int *i)
{
    char *str;
    int n;

	n = 0;
    str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!str)
        return (NULL);
    while (ptr[*i] && !is_separator(ptr[*i]) && ptr[*i] != ' ')
        str[n++] = ptr[(*i)++];
    str[n] = '\0';
    return (str);
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

char *get_separator(char *line, int *i)
{
    int tot_str;
    char *str;

    tot_str = 1;
    if (line[*i] == '>' && line[*i + 1] == '>')
        tot_str = 2;
    str = (char *)malloc(sizeof(char) * (tot_str + 1));
    if (!str)
        return (NULL);
    str[0] = line[*i];
    if (tot_str == 2)
        str[1] = line[*i + 1];
    str[tot_str] = '\0';
    *i += tot_str;
    return (str);
}

void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}

t_token *process_line(char *line)
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

