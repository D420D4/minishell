//
// Created by plefevre on 2/11/22.
//

#include "../includes/minishell.h"

int	is_in_builtin(char *cmd_name)
{
	if (!ft_memcmp(cmd_name, "echo", 5)
		|| !ft_memcmp(cmd_name, "env", 4)
		|| !ft_memcmp(cmd_name, "export", 7)
		|| !ft_memcmp(cmd_name, "unset", 6)
		|| !ft_memcmp(cmd_name, "cd", 3)
		|| !ft_memcmp(cmd_name, "pwd", 4))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->cmd_path == NULL)
		return (0);
	else if (!ft_memcmp(cmd->cmd_path, "echo", 5))
		g_exit_status = cmd_echo(cmd->cmd_argv);
	else if (!ft_memcmp(cmd->cmd_path, "env", 4))
		g_exit_status = cmd_env(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "export", 7))
		g_exit_status = cmd_export(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "unset", 6))
		g_exit_status = cmd_unset(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "cd", 3))
		g_exit_status = cmd_cd(cmd->cmd_argv, data);
	else if (!ft_memcmp(cmd->cmd_path, "pwd", 4))
		g_exit_status = cmd_pwd();
	else
		return (1);
	return (0);
}