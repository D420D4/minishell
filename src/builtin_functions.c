//
// Created by plefevre on 2/11/22.
//

#include "../includes/minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_memcmp(cmd->cmd[0], "echo", 5))
		g_exit_status = cmd_echo(cmd->cmd);
	else if (!ft_memcmp(cmd->cmd[0], "env", 4))
		g_exit_status = cmd_env(cmd, data);
	else if (!ft_memcmp(cmd->cmd[0], "export", 7))
		g_exit_status = cmd_export(cmd, data);
	else if (!ft_memcmp(cmd->cmd[0], "unset", 6))
		g_exit_status = cmd_unset(cmd, data);
	else
		return (0);
	return (1);
}