/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:32:36 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 16:12:43 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/debug.h"

static void exec_cmd_in_child(t_cmd *cmd, t_data *data, int pipefds[2], t_cmd *cmd_parent)
{
	int child;
	char **tab;

	child = fork();
	if (child == -1)
		return (perror("fork"));
	else if (child == 0)
	{
		execSignal();
		if (cmd->pipe != NULL && cmd->pipe->fd_in == pipefds[0])
			close_fd(pipefds[0]);
		if (cmd->cmd_path != NULL && cmd->fd_in >= 0 && cmd->fd_out >= 0)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			dup2(cmd->fd_out, STDOUT_FILENO);
			if (execute_builtin(cmd, 0, data))
			{
				tab = env_to_tab(data->env);
				if (execve(cmd->cmd_path, cmd->cmd, tab))
					perror("execve");
				free_tab(tab);
			}
		}
		close_fd(cmd->fd_in);
		close_fd(cmd->fd_out);
		exit_clean(data, cmd_parent);
		exit(g_exit_status);
	}
	//printf("in %d/ out %d\n",cmd->fd_in, cmd->fd_out);
	cmd->pid = child;
	close_fd(cmd->fd_in);
	close_fd(cmd->fd_out);
}

void cmd_signal(int sig)
{
	if (sig == 2)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	} else if (sig == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_status = 131;
	}
}

int	wait_cmd(t_cmd *cmd, t_cmd *cmd_parent)
{
	int status;

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

int	exec_cmds(t_cmd *cmd, t_cmd *cmd_parent,t_data *data)
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

void	analyseLine(t_cmd *cmd, t_data *data)
{
	if (!cmd)
		return ;
	cmd->cmd = do_redirections(cmd, data);
	analyseLine(cmd->pipe, data);
}

int exec_cmd(t_cmd *cmd, t_cmd *cmd_parent,t_data *data)
{
	int	pipefds[2];
	t_cmd	*temp;

	analyseLine(cmd, data);
	//print_cmd(cmd);
	temp = cmd;
	nothingSignal();
	while (cmd)
	{
		if (cmd->pipe != NULL)
		{
			if (pipe(pipefds) == -1)
				perror("pipe");
			if (cmd->fd_out == 1)
				cmd->fd_out = pipefds[1];
			else
				close_fd(pipefds[1]);
			if ((cmd->pipe)->fd_in == 0)
				(cmd->pipe)->fd_in = pipefds[0];
			else
				close_fd(pipefds[0]);
		}
		cmd->cmd_path = find_cmd_path(cmd->cmd, data->env);
		if (cmd == temp && cmd->pipe == NULL && cmd->fd_in >= 0 && cmd->fd_out >= 0 && !execute_builtin(cmd, cmd_parent,data))
		{
			close_fd(cmd->fd_in);
			close_fd(cmd->fd_out);
			return (1);
		}
		exec_cmd_in_child(cmd, data, pipefds, cmd_parent);
		cmd = cmd->pipe;
	}
	return (wait_cmd(temp, cmd_parent));
}
