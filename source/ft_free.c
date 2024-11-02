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

void	ft_free_tokens(t_token *tokens)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i].str)
	{
		ft_free(tokens[i].str, 1);
		i++;
	}
	ft_free(tokens, 1);
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
