#include "../header/minishell.h"

int		is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int		exec_builtin(char **args, t_mini *mini)
{
	int		result;
	char *pwd;
	result = 1;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
	{
		result = ft_echo(args);
		printf("result: %d\n", result);
	}
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		result = ft_cd(&mini->env_copy, args);
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		if ((pwd = ft_pwd()))
		{
			ft_putstr_fd(pwd, 1);
			ft_putchar_fd('\n', 1);
			free(pwd);
			result = 0;
		}
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
    {
        //ft_env(mini->env);
    }
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
        handle_export(args, &mini->env);
	//if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		//ft_unset(args, &mini->env);
	return (result);
} 