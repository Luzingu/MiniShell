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

static int ft_can_be_add(char *str, int i, int double_quote, int single_quote)
{
	if ((str[i] == 34 || str[i] == 39))
	{
		if ((str[i] == 34 && double_quote == 1) || (!double_quote && !single_quote))
			return (0);
		if ((str[i] == 39 && single_quote == 1) || (!double_quote && !single_quote))
			return (0);
	}
	return (1);
}

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
	int		n;
	int		len_aloc;
	bool	double_quote;
	bool	single_quote;

	n = 0;
	len_aloc = 0;
	double_quote = false;
	single_quote = false;

	while (input[n])
	{
		if (input[n++] == '$' && !single_quote)
			len_aloc += get_variable_length(mini, input, &n);
		else if (ft_can_be_add(input, n, double_quote, single_quote))
			len_aloc++;

		if (input[n] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			n++;
		}
		else if (input[n] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			n++;
		}
	}
	return (len_aloc);
}

static void	expand_variables_loop(t_mini *mini, char *input, char *expanded)
{
	int		n;
	int		i;
	char	*env_value;
	int		j;
	bool	double_quote;
	bool	single_quote;

	n = 0;
	j = 0;
	double_quote = false;
	single_quote = false;

	if (!expanded)
		return ;

	while (input[n])
	{
		if (input[n] == '$' && !single_quote)
		{
			n++;
			env_value = get_env_value(mini, input, &n);
			if (env_value)
			{
				i = 0;
				while (env_value[i])
					expanded[j++] = env_value[i++];
			}
			continue;
		}
		else if (ft_can_be_add(input, n, double_quote, single_quote))
			expanded[j++] = input[n++];

		if (input[n] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			n++;
		}
		else if (input[n] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			n++;
		}
	}
	expanded[j] = '\0';
}


char	*expand_variables(t_mini *mini, char *input)
{
	char	*expanded;
	int		len_aloc;

	len_aloc = ft_get_len_aloc(mini, input);
	expanded = malloc(len_aloc + 1);
	expand_variables_loop(mini, input, expanded);
	return (expanded);
}
