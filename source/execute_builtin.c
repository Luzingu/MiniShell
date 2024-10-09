/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:31:58 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 07:27:43 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

static void	calling_tiny_functions(t_mini *mini, char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		ft_echo(args, mini);
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(mini, args);
	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(args, mini);
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		handle_unset(args, &mini->env);
}

static void	calling_env_function(t_mini *mini, char **args)
{
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
}

static void	calling_pwd_function(t_mini *mini, char **args, int *result)
{
	char	*pwd;

	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
	{
		pwd = ft_pwd(mini);
		if (pwd)
		{
			ft_putstr_fd(pwd, 1);
			ft_putchar_fd('\n', 1);
			free(pwd);
			(*result) = 0;
		}
	}
}

static void	calling_export_function(t_mini *mini, char **args, int *result)
{
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
	{
		if (args[1])
		{
			(*result) = 0;
			while (args[++(*result)])
			{
				if (!ft_strncmp(args[(*result)], "=",
						ft_strlen(args[(*result)]))
					|| !ft_strncmp(args[(*result)], "=", 1))
				{
					ft_putstr_fd("not a valid identifier\n", 2);
					mini->last_return = 1;
					break ;
				}
			}
			handle_export(args, &mini->env, mini);
		}
		else
			ft_env(mini->env);
	}
}

int	exec_builtin(char **args, t_mini *mini)
{
	int	result;

	result = 0;
	calling_tiny_functions(mini, args);
	calling_env_function(mini, args);
	calling_pwd_function(mini, args, &result);
	calling_export_function(mini, args, &result);
	return (result);
}
