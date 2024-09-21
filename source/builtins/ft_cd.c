/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:37 by mcaquart          #+#    #+#             */
/*   Updated: 2024/09/20 17:46:41 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_cd(char **argument)
{
    char *home = getenv("HOME");
    char *path = NULL;

    path = malloc(sizeof(char *) * (ft_strlen(home) + ft_strlen(argument[1]) + 2));
    if (!path)
    {
        perror("malloc");
        exit(1);
    }
    if (!argument[1])
        argument[1] = home;
    if ((argument[0] && !argument[1][0]) || argument[1][0] == '~')
    {
        strcpy(path, home);
        strcat(path, argument[1]++);
        argument[1] = path;
    }
    if (chdir(argument[1]))
        perror("cd");
    free(path);
}
