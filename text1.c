/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:21:53 by aluzingu          #+#    #+#             */
/*   Updated: 2024/08/30 16:21:54 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	while(1)
	{
		char	*entrada;
		
		entrada = readline("$> ");
		if (strncmp(entrada, "exit", 4) == 0)
			exit(0);
		//if (strncmp(entrada, "echo", 4) == 0)
		//{
			char	*argv[4];
			extern char **environ;
			
			argv[0] = "/bin/sh";
			argv[1] = "-C";
			argv[2] = entrada;
			argv[3] = NULL;
			
			if (fork() == 0)
				execve("/bin/sh", argv, environ);
			else
				wait(NULL);
		//}
	}
	return (0);
}
