/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:34:46 by aluzingu          #+#    #+#             */
/*   Updated: 2024/09/04 10:01:46 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

    # include <unistd.h>
    # include <stdio.h>
    # include <stdlib.h>
    # include <string.h>
    # include <sys/wait.h>
    # include <readline/readline.h>
    # include <readline/history.h>
    # include "libft/libft.h"

    void    execute_ve(char *bin, char *argumentos, char **var_ambiente);
    void    ft_free_mtrs(char **matriz);
    void    get_comando(char *str, char **comando, char **argumentos);
    char    *ft_strcat(char *str1, char *str2);

#endif