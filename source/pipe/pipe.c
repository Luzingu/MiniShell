/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:19:11 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/15 18:00:04 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	heredoc(const char *delimiter, int *fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (pipe(fd) == -1)
	{
		perror("Error to create the pipe!");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
		{
			perror("Error to read the line!");
			break ;
		}
		buffer[bytes_read] = '\0';
		if (buffer[bytes_read - 1] == '\n')
		{
			buffer[bytes_read - 1] = '\0';
			bytes_read--;
		}
		if (ft_strncmp(buffer, delimiter, delimiter_len) == 0
			&& buffer[delimiter_len] == '\0')
			break ;
		write(fd[1], buffer, bytes_read);
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	get_input_fd(int *prev_pipe_fd, int i, char **comando)
{
	char	*file;
	char	**mtx_comandos;
	char	redirections[2][3];
	int		w_is;
	int		heredoc_fd[2];
	int		n;
	int		input_tmp;

	if (i != 0)
	{
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
	}
	ft_strlcpy(redirections[0], "<<", 3);
	ft_strlcpy(redirections[1], "<", 2);
	input_tmp = -1;
	n = -1;
	while (++n <= 1)
	{
		mtx_comandos = ft_split_advanced(*comando, redirections[n]);
		if (mtx_comandos[1])
		{
			file = ft_strtrim(mtx_comandos[1], " ");
			if (ft_strncmp(redirections[n], "<<", 2) == 0)
			{
				heredoc(file, heredoc_fd);
				input_tmp = heredoc_fd[0];
			}
			else if (ft_strncmp(redirections[n], "<", 1) == 0)
				input_tmp = open(file, O_RDONLY);
			if (input_tmp != -1)
			{
				dup2(input_tmp, STDIN_FILENO);
				close(input_tmp);
			}
			w_is = whereis(*comando, redirections[n]);
			(*comando)[w_is] = '\0';
			break ;
		}
	}
	ft_free_mtrs(mtx_comandos);
}

void	get_output_fd(int *pipe_fd, int i, int num_comandos, char **comando)
{
	char	*file;
	char	**mtx_comandos;
	char	redirections[2][3];
	int		w_is;
	int		n;
	int		out_tmp;

	if (i != num_comandos - 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	ft_strlcpy(redirections[0], ">>", 3);
	ft_strlcpy(redirections[1], ">", 2);
	out_tmp = -1;
	n = -1;
	while (++n <= 1)
	{
		mtx_comandos = ft_split_advanced(*comando, redirections[n]);
		if (mtx_comandos[1])
		{
			file = ft_strtrim(mtx_comandos[1], " ");
			if (ft_strncmp(redirections[n], ">>", 2) == 0)
				out_tmp = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
			else if (ft_strncmp(redirections[n], ">", 1) == 0)
				out_tmp = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
			if (out_tmp != -1)
			{
				dup2(out_tmp, STDOUT_FILENO);
				close(out_tmp);
			}
			w_is = whereis(*comando, redirections[n]);
			(*comando)[w_is] = '\0';
			break ;
		}
	}
	ft_free_mtrs(mtx_comandos);
}
