/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 05:10:04 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 07:03:33 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	if (head == NULL)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str)
			ft_free(tmp->str, 1);
		if (tmp->type)
			ft_free(tmp->type, 1);
		ft_free(tmp, 1);
	}
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			ft_free(tmp->key, 1);
		if (tmp->value)
			ft_free(tmp->value, 1);
		ft_free(tmp, 1);
	}
}

void	ft_free_all(t_mini *mini)
{
	//free_tokens(mini->start);
	//free_env(mini->env);
	(void)mini;
}
