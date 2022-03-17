/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:59:21 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 12:10:06 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_fork(t_cmd *cmd, t_data *data,
			int pipefds[2], t_cmd *cmd_parent)
{
	char	**tab;

	if (cmd->pipe != NULL && cmd->pipe->fd_in == pipefds[0])
		close_fd(pipefds[0]);
	if (cmd->cmd_path != NULL && cmd->fd_in >= 0 && cmd->fd_out >= 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (execute_builtin(cmd, cmd_parent, data))
		{
			tab = env_to_tab(data->env);
			if (execve(cmd->cmd_path, cmd->cmd, tab))
				perror("execve");
			free_tab(tab);
		}
	}
	close_fd(cmd->fd_in);
	close_fd(cmd->fd_out);
}

static void	exec_child(t_cmd *cmd, t_data *data,
			int pipefds[2], t_cmd *cmd_parent)
{
	int		child;

	child = fork();
	if (child == -1)
		return (perror("fork"));
	else if (child == 0)
	{
		exec_signal();
		exec_fork(cmd, data, pipefds, cmd_parent);
		exit_clean(data, cmd_parent);
		exit(g_exit_status);
	}
	cmd->pid = child;
}

static void	pipe_transition(t_cmd *cmd, int pipefds[2])
{
	if (cmd->pipe != NULL)
	{
		if (pipe(pipefds) == -1)
		{
			perror("pipe");
			if (cmd->fd_out == 1)
				cmd->fd_out = -1;
			if ((cmd->pipe)->fd_in == 0)
				(cmd->pipe)->fd_in = -1;
		}
		else
		{
			if (cmd->fd_out == 1)
				cmd->fd_out = pipefds[1];
			else
				close_fd(pipefds[1]);
			if ((cmd->pipe)->fd_in == 0)
				(cmd->pipe)->fd_in = pipefds[0];
			else
				close_fd(pipefds[0]);
		}
	}
}

int	exec_cmd(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int		pipefds[2];
	t_cmd	*temp;

	analyse_line(cmd, data);
	temp = cmd;
	nothing_signal();
	while (cmd)
	{
		pipe_transition(cmd, pipefds);
		cmd->cmd_path = find_cmd_path(cmd->cmd, data->env);
		if (cmd == temp && cmd->pipe == NULL && cmd->fd_in >= 0
			&& cmd->fd_out >= 0 && !execute_builtin(cmd, cmd_parent, data))
		{
			close_fd(cmd->fd_in);
			close_fd(cmd->fd_out);
			return (1);
		}
		exec_child(cmd, data, pipefds, cmd_parent);
		close_fd(cmd->fd_in);
		close_fd(cmd->fd_out);
		cmd = cmd->pipe;
	}
	return (wait_cmd(temp, cmd_parent));
}
