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

	result = 0;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		result = ft_echo(args);
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		result = ft_cd(&mini->env, args);
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		ft_get_pwd();
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
    {
        //ft_env(mini->env);
    }
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
        handle_export(args, &mini->env);
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		ft_unset(args, &mini->env);
	return (result);
} 