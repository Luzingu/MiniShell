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

static int	ft_is_unclosed_quote(char *str, int i, char quote, t_mini *mini)
{
	if (mini->values.val1 == quote)
		return (0);
	else if (!mini->values.val1)
	{
		while (str[++i])
		{
			if (str[i] == quote)
				return (0);
		}
	}
	return (1);	
}

static int	ft_is_closed(char *str, int i, char quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

static int ft_can_be_add(char *str, int i, t_mini *mini)
{
	if ((str[i] == 34 || str[i] == 39))
	{
		if (str[i] == 34 && ft_is_unclosed_quote(str, i, str[i], mini))
			return (1);
		if (str[i] == 39 && ft_is_unclosed_quote(str, i, str[i], mini))
			return (1);
		if(!mini->values.val1)
			return (0);
		if ((str[i] == 34 && mini->values.val1 == 34))
			return (0);
		if ((str[i] == 39 && mini->values.val1 == 39))
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
	(*n)++;
	if (input[*n] == '?')
	{
		mini->values.str1 = ft_itoa(mini->last_return);
		len_aloc += ft_strlen(mini->values.str1);
		ft_free(mini->values.str1, 1);
		(*n)++;
	}
	else
	{
		env_name = malloc(1000);
		if (!env_name)
			return (0);
		while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
			env_name[i++] = input[(*n)++];
		env_name[i] = '\0';
		mini->values.str1 = ft_getenv(mini->env, env_name);
		len_aloc += ft_strlen(mini->values.str1);
		ft_free(env_name, 1);
	}
	return (len_aloc);
}

static int	ft_get_len_aloc(t_mini *mini, char *input)
{
	int		n;
	int		len_aloc;

	n = 0;
	len_aloc = 0;
	mini->values.val1 = 0;
	while (input[n])
	{
		if (input[n] == '$' && mini->values.val1 != 39)
			len_aloc += get_variable_length(mini, input, &n);
		else
		{
			if (ft_can_be_add(input, n, mini))
				len_aloc++;
			if (input[n] == 34 && mini->values.val1 != 39)
			{
				if (mini->values.val1 != 34)
					mini->values.val1 = 34;
				else
					mini->values.val1 = 0;
			}
			else if (input[n] == 39 && mini->values.val1 != 34)
			{
				if (mini->values.val1 != 39)
					mini->values.val1 = 39;
				else
					mini->values.val1 = 0;
			}
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

	n = 0;
	j = 0;
	mini->values.val1 = 0;
	if (!expanded)
		return ;
	while (input[n])
	{
		if (input[n] == '$' && mini->values.val1 != 39)
		{
			n++;
			env_value = get_env_value(mini, input, &n);
			if (env_value)
			{
				i = 0;
				while (env_value[i])
					expanded[j++] = env_value[i++];
			}
		}
		else
		{
			if (ft_can_be_add(input, n, mini))
				expanded[j++] = input[n];
			if (input[n] == 34 && mini->values.val1 != 39)
			{
				if (mini->values.val1 != 34)
				{
					if (ft_is_closed(input, n, 34))
						mini->values.val1 = 34;
				}
				else
					mini->values.val1 = 0;
			}
			else if (input[n] == 39 && mini->values.val1 != 34)
			{
				if (mini->values.val1 != 39)
				{
					if (ft_is_closed(input, n, 39))
						mini->values.val1 = 39;
				}
				else
					mini->values.val1 = 0;
			}
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
