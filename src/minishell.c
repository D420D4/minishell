//
// Created by plefevre on 1/26/22.
//
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "debug.h"
#include "get_next_line.h"




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
		cmd = getCmd();
		print_cmd(cmd);
	}
	return (0);
}

