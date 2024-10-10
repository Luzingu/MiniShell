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

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

void	ft_free(void *ptr, int free_ptr)
{
	if (!free_ptr)
		return ;
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

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
		//ft_free(tmp, 1);
	}
	head = NULL;
}


void	ft_free_all(t_mini *mini)
{
	free_tokens(mini->start);
	free_env(mini->env);
}