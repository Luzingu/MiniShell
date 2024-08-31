/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:33:26 by mcaquart          #+#    #+#             */
/*   Updated: 2024/08/30 19:16:59 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_COMMANDS 1024
#define MAX_LINE 1024

void	ft_cd(char *path)
{
	if (chdir(path))
		perror("Error\nft_cd.");
}

void	ft_pwd(void)
{
	char	current_work_directory[2048] = {0};

	if (getcwd(current_work_directory, sizeof(current_work_directory)))
		ft_putendl_fd(current_work_directory, 1);
	else
		perror("Error\nft_pwd.");
}

void	ft_ls(void)
{
	DIR		*directory;
	struct dirent	*entry;

	directory = opendir(".");
	if (!directory)
		perror("Error\nft_ls.");
	else
	{
		entry = readdir(directory);
		if (entry)
			ft_putendl_fd(entry->d_name, 1);
		closedir(directory);
	}
}

void	ft_echo(char *arguments)
{
	int	i;

	i = 0;
	if (arguments[i] == 34 || arguments[i] == 39)
		i++;
	while (arguments[i])
	{
		if (arguments[i] == 34 || arguments[i] == 39)
			break ;
		ft_putchar_fd(arguments[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	ft_cat(char **argument)
{
	int	fd;

	fd = open(argument[1], 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp("cat", argument);
}

void	ft_exit(char **matrix)
{
	if (matrix[2])
		perror("Error\n");
	else if (matrix[1] && (ft_atoi(matrix[1]) >= 1))
		exit(1);
	exit(0);
}

int main() {
    char	command[MAX_LINE] = {0};
    char	**args;
    char	*token;
    int		num_args;
    pid_t	pid;

    while (1)
    {
        ft_putstr_fd("minishell> ", 1);
        fgets(command, MAX_LINE, stdin);
        command[strcspn(command, "\n")] = 0;
        num_args = 0;
        token = strtok(command, " ");
	args = malloc(sizeof(char *) * (ft_strlen(command) + 1));
        while (token)
	{
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;
	if (!strcmp(args[0], ""))
		;
	else if (!strcmp(args[0], "exit"))
		ft_exit(args);
	else if (!strcmp(args[0], "cd"))
		ft_cd(args[1]);
	else if (!strcmp(args[0], "echo"))
		ft_echo(args[1]);
	else if (!strcmp(args[0], "ls"))
		ft_ls();
	else if (!strcmp(args[0], "cat"))
		ft_cat(args);
	else
	{
            pid = fork();
            if (!pid)
	    {
                execvp(args[0], args);
                perror("Error!\nexecvp");
                ft_exit(args);
            }
	    wait(NULL);
        }
    }
    free(args);
    return (0);
}
