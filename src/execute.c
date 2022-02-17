/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:32:36 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/16 17:09:55 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/debug.h"

static void	exec_cmd_in_child(t_cmd *cmd, t_data *data, int pipefds[2])
{
	int	child;
	char	**tab;

	execute_builtin(cmd, data);
	child = fork();
	if (child == -1)
		return (perror("fork"));
	else if (child == 0)
	{
		if (!is_in_builtin(cmd->cmd_path))
		{
			tab = NULL;
			if (cmd->pipe != NULL)
				close_fd(pipefds[0]);
			if (cmd->fd_in >= 0 && cmd->fd_out >=0)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				dup2(cmd->fd_out, STDOUT_FILENO);
			}
			close_fd(cmd->fd_in);
			close_fd(cmd->fd_out);
			if (cmd->cmd_path != NULL && cmd->fd_in >= 0 && cmd->fd_out >=0)
			{
				tab = env_to_tab(data->env);
				if (execve(cmd->cmd_path, cmd->cmd_argv, tab))
					perror("execve");
				free_tab(tab);
			}
		}
		free_cmd(cmd);
		exit(g_exit_status);
	}
	//printf("in %d/ out %d\n",cmd->fd_in, cmd->fd_out);
	cmd->pid = child;
	close_fd(cmd->fd_in);
	close_fd(cmd->fd_out);
}

void	wait_cmd(t_cmd *cmd)
{
	int status;

	while(cmd)
	{
		if (waitpid(cmd->pid, &status, 0) == -1)
			perror("waitpid");
		cmd = cmd->pipe;
	}
	g_exit_status = WEXITSTATUS(status);
}

int	exec_cmd(t_cmd *cmd, t_data *data)
{
	int	rd_in;
	int	rd_out;
	int	pipefds[2];
	t_cmd	*temp;

	temp = cmd;
	while(cmd)
	{
		if (cmd->pipe != NULL)
		{
			if (pipe(pipefds) == -1)
				perror("pipe");
			cmd->fd_out = pipefds[1];
			(cmd->pipe)->fd_in = pipefds[0];
		}
		if (find_rd_in(cmd->cmd, &rd_in) || find_rd_output(cmd->cmd, &rd_out))
			return (1);
		if (rd_in != -1)
		{
			close_fd(cmd->fd_in);
			cmd->fd_in = rd_in;
		}
		if (rd_out != -1)
		{
			close_fd(cmd->fd_out);
			cmd->fd_out = rd_out;
		}
		cmd->cmd_path = find_cmd_path(cmd->cmd, data->env);
		cmd->cmd_argv = find_cmd_argv(cmd->cmd, cmd->cmd_path);
		//print_path_argv(cmd);
		
		exec_cmd_in_child(cmd, data, pipefds);
		cmd = cmd->pipe;
	}
	wait_cmd(temp);
	return (0);
}
