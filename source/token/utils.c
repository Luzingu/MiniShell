#include "../../header/minishell.h"

int is_separator(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
}

void    type_arg(t_token *start, t_token *token)
{
   
    size_t len_str;
    t_token *prev;

    prev = prev_sep(start, token);

    len_str = 0;
    if(token->str)
        len_str = ft_strlen(token->str);
    if (!ft_strncmp(token->str, ">", len_str))
        token->type = "trunc";
    else if (!ft_strncmp(token->str, ">>", len_str))
        token->type = "append";
    else if (!ft_strncmp(token->str, "<<", len_str))
        token->type = "heredoc";
    else if (!ft_strncmp(token->str, "<", len_str))
        token->type = "input";
    else if (!ft_strncmp(token->str, "|", len_str))
        token->type = "pipe";
    else if (prev == NULL || ft_is_type(prev, "end") || ft_is_type(prev, "append") || ft_is_type(prev, "input") || ft_is_type(prev, "pipe"))
        token->type = "cmd";
    else
        token->type = "arg";
}

char *get_separator(char *line, int *i)
{
    int tot_str;
    char *str;

    tot_str = 1;
    if (line[*i] == '>' && line[*i + 1] == '>')
        tot_str = 2;
    else if (line[*i] == '<' && line[*i + 1] == '<')
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