/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/04 10:12:53 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *readed;

    char *comando;
    char *args;
    char *bin;
    
    while (1)
    {
        readed = readline("minishell> ");
        if (!readed)
            break;
        get_command(readed, &comando, &args);
        if (ft_strncmp(comando, "echo", 4) == 0)
        	ft_echo(args);
        else if (ft_strncmp(comando, "exit", 4) == 0)
        	ft_exit(ft_split(args, ' '));
        else if (ft_strncmp(comando, "cat", 3) == 0)
        	ft_cat(ft_split(args, ' '));
        else
        {
		    bin = ft_strcat("/bin/", comando);
		    execute_ve(bin, args, NULL);
		}
         free(readed);
    }
   
    return (0);
}
