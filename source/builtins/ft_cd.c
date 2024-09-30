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


void    go_pwd(char *path, char ***env)
{
    char *current_pwd;
    char *past_pwd;

    past_pwd = ft_pwd();
    if (chdir(path))
        perror("cd");
    else
    {
        current_pwd = ft_pwd();
        past_pwd = ft_strjoin("OLDPWD=", past_pwd);
        *env = ft_export(past_pwd, *env);
        current_pwd = ft_strjoin("PWD=", current_pwd);
        *env = ft_export(current_pwd, *env);
    }
}   

int	ft_cd(char ***env, char **argument)
{
    char *path = NULL;
    int total_of_arguments;

    total_of_arguments = nb_args(argument);
    if (total_of_arguments > 2)
    {
        printf("bash: cd: too many arguments\n");
        return (1);
    }

    if (argument[1])
    {
        if (ft_strncmp("-", argument[1], ft_strlen(argument[1])) == 0)
        {
            path = my_getenv(*env, "OLDPWD");
        }
        else if (argument[1][0] == '~')
        {
            path = my_getenv(*env, "HOME");
            path = ft_strjoin(path, &(argument[1][1]));
        }
        else
        {
            path = ft_strdup(argument[1]);
            go_pwd(path, env);
            free(path);
            return (1);
        }
    }
    else
        path = my_getenv(*env, "HOME");
    go_pwd(path, env);
    return (1);    
}
