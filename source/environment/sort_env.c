/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:04:21 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:04:23 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*concat_key_value(t_env *env)
{
	int		len;
	char	*key_value;

	if (!env || !env->key || !env->value)
		return (NULL);
	len = strlen(env->key) + strlen(env->value) + 2;
	key_value = malloc(len);
	if (!key_value)
		return (NULL);
	snprintf(key_value, len, "%s=%s", env->key, env->value);
	return (key_value);
}

static int	compare_env_vars(t_env *a, t_env *b)
{
	char	*a_str;
	char	*b_str;
	int		result;

	a_str = concat_key_value(a);
	b_str = concat_key_value(b);
	if (!a_str || !b_str)
	{
		free(a_str);
		free(b_str);
		return (0);
	}
	result = strcmp(a_str, b_str);
	free(a_str);
	free(b_str);
	return (result);
}

static t_env	*sorted_insert(t_env *sorted, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return (sorted);
	if (!sorted || compare_env_vars(new_node, sorted) < 0)
	{
		new_node->next = sorted;
		return (new_node);
	}
	current = sorted;
	while (current->next && compare_env_vars(new_node, current->next) >= 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (sorted);
}

t_env	*sort_env_list(t_env *head)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*next;

	if (!head)
		return (NULL);
	sorted = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		sorted = sorted_insert(sorted, current);
		current = next;
	}
	return (sorted);
}
