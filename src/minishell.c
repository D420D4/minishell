/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:44:36 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/17 12:03:34 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int	g_exit_status = 0;


void print_cmd(t_cmd *cmd)
{
	if  (!cmd)
		return;
	int i;

	i = 0;
	if(!cmd)
	{
		printf("ERROR cmd\n");
		return;
	}
	if (cmd->soon)
		print_cmd(cmd->soon);
	else
	{
		printf ("%d << >> %d : ", cmd->fd_in, cmd->fd_out);
		if (cmd->cmd == NULL)
			printf("[] = NULL");
		while (cmd->cmd && cmd->cmd[i])
		{
			printf("[%s] ", cmd->cmd[i]);
			i++;
		}
		printf("\n");
		if (cmd->pipe)
		{
			printf("| ");
			print_cmd(cmd->pipe);
		}
	}
	if (cmd->on_success)
	{
		printf("&& ");
		print_cmd(cmd->on_success);
	}
	if (cmd->on_fail)
	{
		printf("|| ");
		print_cmd(cmd->on_fail);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_cmd	*cmd;

	(void) av;
	(void) ac;
	data.env = parse_env(envp);
	add_pwd(&data);
	print_header();
	while (42)
	{
		get_cmd_signal();
		cmd = get_cmd(&data);
		if (cmd)
			exec_cmds(cmd, cmd, &data);
		else
		{
			g_exit_status = 0;
			cmd_exit(cmd, cmd, &data);
		}
		//print_cmd(cmd);
		free_cmd(cmd);
	}
	exit_clean(&data, NULL);
	return (0);
}
