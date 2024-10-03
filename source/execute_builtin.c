/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:31:58 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:43:22 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

int		is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int		exec_builtin(char **args, t_mini *mini)
{
	int		result;
	char	*pwd;

	result = 1;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		ft_echo(args, mini);
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(mini, args);
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
	{
		if ((pwd = ft_pwd(mini)))
		{
			ft_putstr_fd(pwd, 1);
			ft_putchar_fd('\n', 1);
			free(pwd);
			result = 0;
		}
	}
	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(args, mini);
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
	{
		if (args[1])
		{
			ft_putstr_fd("too many arguments\n", 2);
			mini->last_return = 1;
		}
		else
			ft_env(mini->env);
	}
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
	{
		if (args[1])
		{
			result = 1;
			while (args[result])
			{
				if(ft_strncmp(args[result], "=", ft_strlen(args[result])) == 0 || ft_strncmp(args[result], "=", 1) == 0)
				{
					ft_putstr_fd("not a valid identifier\n", 2);
					mini->last_return = 1;
					break;
				}
				result++;
			}
			handle_export(args, &mini->env, mini);
		}
		else
			ft_env(mini->env);
	}
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		handle_unset(args, &mini->env);
	return (result);
} 
