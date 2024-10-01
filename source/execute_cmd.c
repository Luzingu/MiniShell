#include "../header/minishell.h"


char *find_executable(char *cmd, char **env)
{
    struct stat buffer;

    if (stat(cmd, &buffer) == 0)
        return strdup(cmd);

    char *path_env = ft_getenv(env, "PATH");
    if (!path_env)
        return (NULL);

    char **path_dirs = ft_split(path_env, ':');
    for (int i = 0; path_dirs[i]; i++)
    {
        char *full_path = ft_strjoin(ft_strjoin(path_dirs[i], "/"), cmd);
        if (full_path && stat(full_path, &buffer) == 0)
        {
            ft_free_matrix(path_dirs);
            return full_path;
        }
        free(full_path);
    }
    ft_free_matrix(path_dirs);
    return NULL;
}

void execute_cmd(t_mini *mini, char **cmd)
{
    pid_t pid;
    int status;

    if (mini->charge == 0)
        return ;
    pid = fork();
    if (pid == 0)
    {
        char *cmd_path = find_executable(cmd[0], mini->env);
        if (cmd_path)
            execve(cmd_path, cmd, mini->env);
        else
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            exit(127);
        }
    }
    else
        waitpid(pid, &status, 0);
    mini->charge = 0;
}