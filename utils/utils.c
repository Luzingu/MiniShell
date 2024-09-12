/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:40:40 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/12 12:41:51 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_echo(char *argument, int fd)
{
	int	i;

	i = 0;
	if (argument[i] == 34 || argument[i] == 39)
		i++;
	while (argument[i])
	{
		if (argument[i] == 34 || argument[i] == 39)
			break ;
		ft_putchar_fd(argument[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	ft_exit(char **matrix)
{
	if (matrix[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_free_mtrs(matrix);
		return ;
	}
	else if (matrix[0] && (ft_atoi(matrix[0]) >= 1))
		exit(1);
	exit(0);
}


void	ft_cat(char **argument)
{
	int	fd;

	fd = open(argument[0], 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp("cat", argument);
}


void ft_free_mtrs(char **matriz)
{
    int i;
    if (!matriz)
        return ;
    i = 0;
    while (matriz[i])
    {
        free(matriz[i]);
        i++;
    }
    free(matriz);
}

char    *ft_strcat(char *str1, char *str2)
{
    int i;
    int n;
    char    *str;

    i = ft_strlen(str1) + ft_strlen(str1);
    str = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    n = 0;
    while (str1[n])
        str[i++] = str1[n++];
    n = 0;
    while (str2[n])
        str[i++] = str2[n++];
    str[i] = '\0';
    return (str);
}

void get_command(char *str, char **command, char **argument)
{
    int i, total, length;
    char	**matrix;

    matrix = ft_split(str, ' ');
    if (!matrix)
        return;
    if (matrix[0])
        *command = ft_strdup(matrix[0]);
    else
        *command = NULL;
    total = 0;
    i = 0;
    while (matrix[++i])
    	total += (int)ft_strlen(matrix[i]) + 1;
    *argument = (char *)malloc(total + 1);
    if (!(*argument))
    {
        ft_free_mtrs(matrix);
        return ;
    }
    length = 0;
    i = 0;
    while (matrix[++i])
    {
        strcpy(*argument + length, matrix[i]);
        length += strlen(matrix[i]);
        if (matrix[i + 1])
            (*argument)[length++] = ' ';
    }
    (*argument)[length] = '\0';
    ft_free_mtrs(matrix);
}

char **ft_split_advanced(const char *s, const char *delimiter)
{
    size_t len = strlen(s);
    size_t delimiter_len = strlen(delimiter);
    size_t i = 0, start = 0, count = 0;
    char **result;
    char in_single_quotes = 0;
    char in_double_quotes = 0;

    while (i < len) {
        if (s[i] == '\'')
        {
            in_single_quotes = !in_single_quotes;
        }
        else if (s[i] == '\"')
        {
            in_double_quotes = !in_double_quotes;
        }
        else if (!in_single_quotes && !in_double_quotes)
        {
            if (i + delimiter_len <= len && ft_strncmp(s + i, delimiter, delimiter_len) == 0)
            {
                ++count;
                i += delimiter_len - 1;
            }
        }
        ++i;
    }
    ++count;
    
    result = (char **)malloc((count + 1) * sizeof(char *));
    if (!result) return NULL;

    count = 0;
    i = 0;
    in_single_quotes = 0;
    in_double_quotes = 0;
    while (i < len) {
        if (s[i] == '\'') {
            in_single_quotes = !in_single_quotes;
        } else if (s[i] == '\"') {
            in_double_quotes = !in_double_quotes;
        } else if (!in_single_quotes && !in_double_quotes) {
            if (i + delimiter_len <= len && ft_strncmp(s + i, delimiter, delimiter_len) == 0)
            {
                result[count] = ft_strdup(s + start);
                if (!result[count])
                {
                    while (count > 0) {
                        free(result[--count]);
                    }
                    free(result);
                    return NULL;
                }
                result[count][i - start] = '\0';
                ++count;
                start = i + delimiter_len;
                i += delimiter_len - 1;
            }
        }
        ++i;
    }
    result[count] = ft_strdup(s + start);
    if (!result[count])
    {
        while (count > 0) {
            free(result[--count]);
        }
        free(result);
        return NULL;
    }
    result[count + 1] = NULL;
    return result;
}


void    execute_ve(char *bin, char *argument, char **var_ambiente, int input_fd, int output_fd)
{
    int		total_arguments;
    int		i;
    char	**args;
    char	**str_tmp;
    
    if (input_fd != STDIN_FILENO)
    {
        if (dup2(input_fd, STDIN_FILENO) == -1) {
            perror("dup2 input_fd");
            exit(EXIT_FAILURE);
        }
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO)
    {
        if (dup2(output_fd, STDOUT_FILENO) == -1) {
            perror("dup2 output_fd");
            exit(EXIT_FAILURE);
        }
        close(output_fd);
    }
    total_arguments = 0;
    str_tmp = ft_split(argument, ' ');
    while (str_tmp[total_arguments])
        total_arguments++;
    args = (char **)malloc(sizeof(char *) * (total_arguments + 3));
    args[0] = ft_strdup((const char *)bin);
    i = -1;
    while(++i < total_arguments)
        args[(i + 1)] = ft_strdup((const char *)str_tmp[i]);
    args[(i + 1)] = NULL;
    execve(args[0], args, var_ambiente);
    
    ft_free_mtrs(str_tmp);
    ft_free_mtrs(args);
    ft_free_mtrs(var_ambiente);
}
