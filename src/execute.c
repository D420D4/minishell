/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:32:36 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 20:06:22 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analyse_line(t_cmd *cmd, t_data *data)
{
	if (!cmd)
		return ;
	cmd->cmd = do_redirections(cmd, data);
	analyse_line(cmd->pipe, data);
}

int	exec_cmds(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	if (cmd->soon)
	{
		if (!exec_cmds(cmd->soon, cmd_parent, data))
			return (0);
	}
	else
	{
		if (!exec_cmd(cmd, cmd_parent, data))
			return (0);
	}
	if (cmd->on_fail && g_exit_status)
	{
		if (!exec_cmds(cmd->on_fail, cmd_parent, data))
			return (0);
	}
	if (cmd->on_success && !g_exit_status)
	{
		if (!exec_cmds(cmd->on_success, cmd_parent, data))
			return (0);
	}
	return (1);
}

int	wait_cmd(t_cmd *cmd, t_cmd *cmd_parent)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid != -1)
		{
			if (waitpid(cmd->pid, &status, 0) == -1)
				perror("waitpid");
			if (cmd_parent->bonus && __WIFSIGNALED(status))
			{
				cmd_signal(WTERMSIG(status));
				return (0);
			}
		}
		cmd = cmd->pipe;
	}
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (__WIFSIGNALED(status))
	{
		cmd_signal(WTERMSIG(status));
		return (0);
	}
	return (1);
}
