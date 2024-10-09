/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:03:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:03:33 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	get_variable_length(t_mini *mini, char *input, int *n)
{
	char	*env_name;
	int		i;
	int		len_aloc;

	i = 0;
	len_aloc = 0;
	if (input[*n] == '?')
	{
		len_aloc += ft_strlen(ft_itoa(mini->last_return));
		(*n)++;
	}
	else
	{
		env_name = malloc(100);
		if (!env_name)
			return (0);
		while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
			env_name[i++] = input[(*n)++];
		env_name[i] = '\0';
		len_aloc += ft_strlen(ft_getenv(mini->env, env_name));
		free(env_name);
	}
	return (len_aloc);
}

static int	ft_get_len_aloc(t_mini *mini, char *input)
{
	int	n;
	int	len_aloc;

	n = 0;
	len_aloc = 0;
	while (input[n])
	{
		if (input[n++] == '$')
			len_aloc += get_variable_length(mini, input, &n);
		else
			len_aloc++;
	}
	return (len_aloc);
}

static void	expand_variables_loop(t_mini *mini, char *input, char *expanded,
			int *len_aloc)
{
	int		n;
	int		i;
	char	*env_value;

	n = 0;
	i = 0;
	if (!expanded)
		return ;
	while (input[n])
	{
		if (input[n] == '$')
		{
			n++;
			env_value = get_env_value(mini, input, &n);
			if (env_value)
			{
				i = 0;
				while (env_value[i])
					expanded[(*len_aloc)++] = env_value[i++];
			}
		}
		else
			expanded[(*len_aloc)++] = input[n++];
	}
}

char	*expand_variables(t_mini *mini, char *input)
{
	char	*expanded;
	int		len_aloc;

	len_aloc = ft_get_len_aloc(mini, input);
	expanded = malloc(len_aloc + 1);
	len_aloc = 0;
	expand_variables_loop(mini, input, expanded, &len_aloc);
	expanded[len_aloc] = '\0';
	free(input);
	return (expanded);
}
