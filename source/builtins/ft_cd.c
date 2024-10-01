/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:37 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/01 00:12:02 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	go_pwd(char *path, char ***env, t_mini *mini)
{
	char	*current_pwd;
	char	*past_pwd;

	past_pwd = ft_pwd(mini);
	if (chdir(path))
	{
		printf("cd: no such file or directory: %s\n", path);
		mini->last_return = 1;
	}
	else
	{
		current_pwd = ft_pwd(mini);
		past_pwd = ft_strjoin("OLDPWD=", past_pwd);
		*env = ft_export(past_pwd, *env);
		current_pwd = ft_strjoin("PWD=", current_pwd);
		*env = ft_export(current_pwd, *env);
		mini->last_return = 0;
	}
}

void	ft_cd(char ***env, char **argument, t_mini *mini)
{
	char	*path;
	int		total_of_arguments;

	path = NULL;
	total_of_arguments = numb_split(argument);
	if (total_of_arguments > 2)
	{
		printf("bash: cd: too many arguments\n");
		mini->last_return = 1;
		return ;
	}
	if (argument[1])
	{
		if (ft_strncmp("-", argument[1], ft_strlen(argument[1])) == 0)
			path = ft_getenv(*env, "OLDPWD");
		else if (argument[1][0] == '~')
		{
			path = ft_getenv(*env, "HOME");
			path = ft_strjoin(path, &(argument[1][1]));
		}
		else
		{
			path = ft_strdup(argument[1]);
			go_pwd(path, env, mini);
			return ;
		}
	}
	else
		path = ft_getenv(*env, "HOME");
	go_pwd(path, env, mini); 
}