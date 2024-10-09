/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:04:05 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:04:07 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_unset(char *args, t_env **env)
{
	t_env	*env_tmp;
	t_env	*prev;

	env_tmp = *env;
	prev = NULL;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->key, args, ft_strlen(args)) == 0)
		{
			if (!prev)
				*env = env_tmp->next;
			else
				prev->next = env_tmp->next;
			free(env_tmp->key);
			free(env_tmp->value);
			free(env_tmp);
			break ;
		}
		prev = env_tmp;
		env_tmp = env_tmp->next;
	}
}
