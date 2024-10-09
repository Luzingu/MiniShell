/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:07:15 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:07:17 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, var) == 0)
			return (env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}
