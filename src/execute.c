/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:32:36 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/01 19:44:19 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/debug.h"

static void	exec_cmd_in_child(t_cmd *cmd, t_data *data, int pipefds[2])
{
	int	child;
	char	**tab;

	child = fork();
	if (child == -1)
		return (perror("fork"));
	else if (child == 0)
	{
		execSignal();
		ft_putstr_fd("Quit (core dumped)\n", 1);
		if (execute_builtin(cmd, data))
		{
			tab = NULL;
			if (cmd->pipe != NULL)
				close_fd(pipefds[0]);
			if (cmd->fd_in >= 0 && cmd->fd_out >=0)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				dup2(cmd->fd_out, STDOUT_FILENO);
			}
			if (cmd->cmd_path != NULL && cmd->fd_in >= 0 && cmd->fd_out >=0)
			{
				tab = env_to_tab(data->env);
				if (execve(cmd->cmd_path, cmd->cmd_argv, tab))
					perror("execve");
				free_tab(tab);
			}
		}
		close_fd(cmd->fd_in);
		close_fd(cmd->fd_out);
		free_cmd(cmd); // envoyer temp ??
		ft_lstclear(&(data->env), &free);
		exit_clean();
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
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

int	exec_cmd(t_cmd *cmd, t_data *data)
{
	int	rd_in;
	int	pipefds[2];
	t_cmd	*temp;

	temp = cmd;
	while(cmd)
	{
		if (cmd->pipe != NULL)
		{
			if (pipe(pipefds) == -1)
				perror("pipe");
			if (cmd->fd_out == 1)
				cmd->fd_out = pipefds[1];
			else
				close_fd(pipefds[1]);
			(cmd->pipe)->fd_in = pipefds[0];
		}
		if (cmd->cmd && find_rd_in(cmd->cmd, &rd_in))
			return (1);
		if (cmd->cmd && rd_in != -1)
		{
			close_fd(cmd->fd_in);
			cmd->fd_in = rd_in;
		}
		cmd->cmd_path = find_cmd_path(cmd->cmd, data->env);
		cmd->cmd_argv = find_cmd_argv(cmd->cmd, cmd->cmd_path);
		//print_path_argv(cmd);
		if (cmd == temp && cmd->pipe == NULL && !execute_builtin(cmd, data))
			return (0);
		exec_cmd_in_child(cmd, data, pipefds);
		cmd = cmd->pipe;
	}
	wait_cmd(temp);
	return (0);
}
