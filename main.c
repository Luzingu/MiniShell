/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:31:44 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/02 11:57:11 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *readed;
    while (1)
    {
        readed = readline("minishell>");
        if (!readed)
            break;
        if (strcmp(readed, "ls") >= 0)
        {
            execute_ve("/bin/ls", "-la", NULL);
        }
         free(readed);
    }
   
    return (0);
}