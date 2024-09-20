/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/16 09:03:54 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

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

void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
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
        readed = ft_strcat(readed, continuation);
        if (!has_unclosed_quotes(readed, &quote_type))
            break;
        readed = ft_strcat(readed, "\n");
    }
    return (readed);
}

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

char *execute_commands(char **commands) {
    int fd_in = 0;
    char *result = NULL;

    for (int i = 0; commands[i]; i++) {
        int pipefd[2];
        if (commands[i + 1] && pipe(pipefd) == -1) {
            perror("pipe");
            return NULL;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return NULL;
        }

        if (pid == 0) {
            if (fd_in != 0) dup2(fd_in, 0); // Redireciona a entrada padrão
            if (commands[i + 1]) dup2(pipefd[1], 1); // Redireciona a saída padrão se houver próximo comando
            if (commands[i + 1]) close(pipefd[0]);
            execl("/bin/sh", "sh", "-c", commands[i], NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } else {
            if (fd_in != 0) close(fd_in);
            if (commands[i + 1]) close(pipefd[1]);
            fd_in = pipefd[0];
            wait(NULL); // Espera o processo filho terminar
        }
    }

    return result; // Retorna NULL para comandos simples, poderia ser aprimorado
}

int main(void)
{
    char *readed;
    char **mtx_comandos;

    handle_signals();
    while (1)
    {
        readed = read_input();
        if (!readed)
            break ;
        add_history(readed);
        mtx_comandos = ft_split_advanced(readed, "|");
		execute_commands(mtx_comandos);
        
        free(readed);
        ft_free_mtrs(mtx_comandos);
    }
    return 0;
}

