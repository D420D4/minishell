//
// Created by plefevre on 1/26/22.
//
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "debug.h"
#include "get_next_line.h"



int g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	t_data data;
	t_cmd *cmd;

	(void) ac;
	(void) av;
	(void) envp;
	(void) data;
	data.env = parse_env(envp);
	cmd = 0;

	while (!cmd || ft_memcmp(cmd->cmd[0], "exit", 5))
	{
		getCmdSignal();
		cmd = getCmd(&data);
		if (cmd)
			print_cmd(cmd);
		else
		{
			ft_putstr_fd("\n", 1);
			break;
		}
		//TODO mettre lexecute builtin dans exe_cmd, les builtin ne prennent pas en compte les pipe!!!!
		if (!execute_builtin(cmd, &data))
			exec_cmd(cmd, data);
		printf("----------------- $? = %d -----------\n", g_exit_status);
		//print_cmd(cmd);
	}

	if (cmd && !ft_memcmp(cmd->cmd[0], "exit", 5))
		return (ft_atoi(cmd->cmd[1]));
	return (0);
}

