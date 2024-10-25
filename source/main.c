/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:31:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 06:40:47 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)argv;
	reset_fds(&mini);
	str_dup_env(env, &mini);
	
	mini.last_return = 0;
	mini.exit_status = 0;
	mini.no_exec = 0;
	mini.tokens = NULL;
	handle_signals();
	main_loop(&mini);
	return (mini.last_return);
}
