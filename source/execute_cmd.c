/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:47:49 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:45:09 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*error_message(char *path, t_mini *mini)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		mini->last_return = 127;
	else
		mini->last_return = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (NULL);
}

static char	*find_executable(char *cmd, t_mini *mini, int i)
{
	struct stat	buffer;
	char		**path_dirs;
	char		*path_env;
	char		*full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		if (stat(cmd, &buffer) == 0)
			return (ft_strdup(cmd));
	path_env = ft_getenv(mini->env, "PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	while (path_dirs[++i])
	{
		full_path = ft_strjoin2(ft_strjoin(path_dirs[i], "/"), cmd, 1, 0);
		if (full_path && stat(full_path, &buffer) == 0)
		{
			ft_free_matrix(path_dirs);
			return (full_path);
		}
		ft_free(full_path, 1);
	}
	ft_free_matrix(path_dirs);
	return (NULL);
}

void	execute_cmd(t_mini *mini, char **cmd)
{
	pid_t	pid;
	int		status;
	char	**env_matrix;
	char	*cmd_path;

	if (mini->charge == 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		cmd_path = find_executable(cmd[0], mini, -1);
		if (cmd_path)
		{
			env_matrix = env_to_matrix(mini->env, 0);
			execve(cmd_path, cmd, env_matrix);
			ft_free_matrix(env_matrix);
			ft_free(cmd_path, 1);
		}
		else
		{
			error_message(cmd[0], mini);
			mini->parent = 0;
		}
	}
	else
		waitpid(pid, &status, 0);
	mini->charge = 0;
}
