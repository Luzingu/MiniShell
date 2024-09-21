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

char **ft_export(char *args, char **env)
{
    char *name_v;
    char *value;
    int i;
    char **new_env;
    int exist = 0;
    char *str;

    i = whereis(args, "=");
    if (i == -1)
    {
        printf("Erro: '=' não encontrado no argumento.\n");
        return (NULL);
    }
    name_v = ft_substr(args, 0, i);
    value = ft_substr(args, i + 1, ft_strlen(args) - i - 1);
    str = ft_strdup(name_v);
    str = ft_strcat(str, "=");
    str = ft_strcat(str, value);
    i = 0;
    while (env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        printf("Erro ao alocar memória.\n");
        return (NULL);
    }

    i = 0;
    exist = 0;
    while (env[i])
    {
        if (ft_strncmp(name_v, env[i], ft_strlen(name_v)) == 0 && env[i][ft_strlen(name_v)] == '=')
        {
            new_env[i] = ft_strdup(str);
            exist = 1;
        }
        else
            new_env[i] = ft_strdup(env[i]);
        i++;
    }
    if (!exist)
        new_env[i++] = ft_strdup(str);
    new_env[i] = NULL;
    ft_free_mtrs(env);
    free(name_v);
    free(value);
    free(str);
    return (new_env);
}


char **ft_unset(char *args, char ***env)
{
    int i = 0;
    int j = 0;
    char **new_env;

    // Adicione um "=" para facilitar a comparação
    char *to_remove = ft_strcat(args, "=");

    while ((*env)[i])
        i++;

    new_env = malloc(sizeof(char *) * i); // Tamanho máximo sem a variável a ser removida
    if (!new_env)
    {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp(to_remove, (*env)[i], ft_strlen(to_remove)) != 0)
        {
            new_env[j++] = ft_strdup((*env)[i]); // Copie a variável se não for a que está sendo removida
        }
        i++;
    }
    new_env[j] = NULL;
    ft_free_mtrs(*env); // Libera a memória do ambiente antigo
    free(to_remove); // Libera a memória da string temporária
    return new_env; // Retorna o novo ambiente
}


void handle_export(char **tmp, char ***env)
{
    int n = 1;
    while (tmp[n])
    {
        *env = ft_export(tmp[n], *env); // Supomos que ft_export é segura
        n++;
    }
}

void handle_unset(char **tmp, char ***env)
{
    int n = 1;
    while (tmp[n])
    {
        *env = ft_unset(tmp[n], env); // Supomos que ft_export é segura
        n++;
    }
}

char *my_getenv(char **env, const char *name)
{
    size_t name_len = ft_strlen(name);

    for (int i = 0; env[i] != NULL; i++) 
    {
        // Verifica se a variável começa com o nome e é seguida de '='
        if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
        {
            return &env[i][name_len + 1];
        }
    }
    return NULL;
}

int is_executable(const char *path)
{
    struct stat st;
    return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR));
}

char *concat_paths(char *dir, char *cmd)
{
    return ft_strjoin(ft_strjoin(dir, "/"), cmd);
}

char *find_executable(char *cmd, char **env)
{
    struct stat buffer;

    if (stat(cmd, &buffer) == 0)
    {
        return strdup(cmd);
    }

    char *path_env = my_getenv(env, "PATH");
    if (!path_env)
        return (NULL);

    char **path_dirs = ft_split(path_env, ':');
    for (int i = 0; path_dirs[i]; i++)
    {
        char *full_path = concat_paths(path_dirs[i], cmd);
        if (full_path && stat(full_path, &buffer) == 0) {
            ft_free_mtrs(path_dirs);
            return full_path;
        }
        free(full_path);
    }
    ft_free_mtrs(path_dirs);
    return NULL;
}

// Função para criar pipes e executar comandos
int exec_command(char *command, int fd_in, int pipefd[2], char **env)
{
    pid_t pid;
    char **args;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) // Processo filho
    {
        if (fd_in != 0) {
            dup2(fd_in, 0); // Redireciona a entrada para o comando
            close(fd_in); // Fechar o descritor após duplicar
        }
        if (pipefd[1] != -1) {
            dup2(pipefd[1], 1); // Redireciona a saída para o próximo pipe
            close(pipefd[1]);   // Fecha o descritor após duplicar
        }
        
        close(pipefd[0]); // Fecha o lado de leitura do pipe

        args = (char **)malloc(sizeof(char *) * 4);
        args[0] = "/bin/sh";
        args[1] = "-c";
        args[2] = command;
        args[3] = NULL;
        execve("/bin/sh", args, env); // Executa o comando
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Processo pai fecha os pipes e espera o filho
    if (fd_in != 0) {
        close(fd_in); // Fecha o descritor de leitura anterior
    }
    if (pipefd[1] != -1) {
        close(pipefd[1]); // Fecha o descritor de escrita do pipe
    }

    wait(NULL); // Aguarda o processo filho

    return pipefd[0]; // Retorna o descritor para leitura do próximo comando
}

// Função principal para executar comandos
char *execute_commands(char **commands, char ***env)
{
    int fd_in = 0;
    int pipefd[2];
    char **tmp;
    int i = 0;

    while (commands[i])
    {
        tmp = ft_split_advanced(commands[i], "<<");
        if (tmp[1]) // Heredoc
        {
            fd_in = read_heredoc(tmp[1]);
            ft_free_mtrs(tmp);
            i++;
            continue;
        }
        ft_free_mtrs(tmp);
        tmp = ft_split_advanced(commands[i], " ");

        if (ft_strncmp(tmp[0], "unset", 5) == 0)
        {
            if (tmp[1])
                handle_unset(tmp, env);
            i++;
            continue;
        }
        if (!find_executable(tmp[0], *env))
        {
            printf("Nao existe nenhum executavel encontrado. \n");
            i++;
            continue;
        }
        if (ft_strncmp(tmp[0], "export", 6) == 0 && tmp[1])
        {
            handle_export(tmp, env);
            ft_free_mtrs(tmp);
            i++;
            continue;
        }
        else if (ft_strncmp(tmp[0], "env", 3) == 0 && tmp[1])
        {
            i++;
            continue;
        }

        if (commands[i + 1]) // Não é o último comando
        {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                ft_free_mtrs(tmp);
                return NULL;
            }
        } 
        else
        {
            pipefd[0] = -1; // Descritor de leitura não é necessário
            pipefd[1] = -1; // Descritor de escrita não é necessário
        }

        fd_in = exec_command(commands[i], fd_in, pipefd, *env);
        if (fd_in == -1) {
            //ft_free_mtrs(tmp);
            return NULL;
        }

        //ft_free_mtrs(tmp);
        i++;
    }

    return NULL;
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *readed;
    char **mtx_comandos;
    char **my_env;

    int i  = 0;
    while (env[i])
        i++;
    my_env = (char **)malloc(sizeof(char *) * (i+1));
    i = 0;
    while (env[i])
    {
        my_env[i] = strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;

    handle_signals();
    while (1)
    {
        readed = read_input();
        if (!readed)
            break ;
        add_history(readed);
        mtx_comandos = ft_split_advanced(readed, "|");
        execute_commands(mtx_comandos, &my_env);
        free(readed);
        ft_free_mtrs(mtx_comandos);
    }


    return 0;
}

