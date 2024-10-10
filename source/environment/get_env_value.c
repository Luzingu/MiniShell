/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:04:14 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:17:44 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_value(t_mini *mini, char *input, int *n)
{
	char	*env_name;
	int		i;

	i = 0;
	if (input[*n] == '?')
	{
		env_name = ft_itoa(mini->last_return);
		(*n)++;
	}
	else
	{
		env_name = malloc(1000);
		if (!env_name)
			return (NULL);
		while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
		{
			env_name[i++] = input[(*n)++];
		}
		env_name[i] = '\0';
		env_name = ft_getenv(mini->env, env_name);
	}
	return (env_name);
}
