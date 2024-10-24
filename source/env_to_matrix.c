/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:14:58 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:45:13 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**env_to_matrix(t_env *env, int i)
{
	t_env	*env_tmp;
	char	**matrix;
	char	*tmp;

	env_tmp = env;
	while (env_tmp)
	{
		i++;
		env_tmp = env_tmp->next;
	}
	matrix = (char **)malloc(sizeof(char *) * (i + 1));
	env_tmp = env;
	i = 0;
	while (env_tmp)
	{
		tmp = ft_strdup(env_tmp->key);
		tmp = ft_strjoin2(tmp, "=", 1, 0);
		if (env_tmp->value)
			tmp = ft_strjoin2(tmp, env_tmp->value, 1, 0);
		if (tmp)
			matrix[i++] = tmp;
		env_tmp = env_tmp->next;
	}
	matrix[i] = NULL;
	return (matrix);
}
