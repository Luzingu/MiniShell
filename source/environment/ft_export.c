/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:10 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:03:56 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/minishell.h"

static char	*get_env_values(char **args_split)
{
	int		i;
	char	*env_value;

	i = 1;
	env_value = NULL;
	while (args_split[i])
	{
		if (i == 1)
			env_value = ft_strdup(args_split[i]);
		else
			env_value = ft_strjoin(env_value, args_split[i]);
		if (args_split[i + 1])
			env_value = ft_strjoin(env_value, "=");
		i++;
	}
	return (env_value);
}

static int	ft_modify_env(t_env *env, char *env_name, char *env_value)
{
	if (ft_strncmp(env->key, env_name, ft_strlen(env_name)) == 0)
	{
		env->value = ft_strdup(env_value);
		return (0);
	}
	return (1);
}

void	ft_export(char *args, t_env **env)
{
	t_env	*env_tmp;
	char	*env_name;
	char	*env_value;
	char	**args_split;
	int		new_env;

	env_tmp = *env;
	args_split = ft_split(args, '=');
	env_name = args_split[0];
	env_value = get_env_values(args_split);
	new_env = 1;
	while (env_tmp && env_tmp->next)
	{
		new_env = ft_modify_env(env_tmp, env_name, env_value);
		if (new_env == 0)
			break ;
		env_tmp = env_tmp->next;
	}
	if (new_env == 1)
		new_env = ft_modify_env(env_tmp, env_name, env_value);
	if (new_env == 1)
		env_tmp->next = add_envirenoment(env_name, env_value);
	ft_free_matrix(args_split);
}
