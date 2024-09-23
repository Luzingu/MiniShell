/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/16 09:03:54 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}



void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}



int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *readed;
    char **mtx_comandos;
    char **my_env;

    int i  = 0;
    while (env[i])
        i++;
    my_env = (char **)malloc(sizeof(char *) * (i+1));
    i = 0;
    while (env[i])
    {
        my_env[i] = strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;

    handle_signals();
    while (1)
    {
        readed = read_input();
        if (!readed)
            break ;
        add_history(readed);
        mtx_comandos = ft_split_advanced(readed, "|");
        execute_commands(mtx_comandos, &my_env);
        free(readed);
        ft_free_mtrs(mtx_comandos);
    }


    return 0;
}

