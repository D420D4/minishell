//
// Created by plefevre on 1/26/22.
//
#include "minishell.h"
#include "debug.h"
#include "get_next_line.h"

int g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	t_data data;
	t_cmd *cmd;

	(void) av;
	(void) ac;
	/*
	if (!isatty(0)) // gestion de /dev/urandom 
	{
		perror("isatty");
		return (1);
	}*/
	data.env = parse_env(envp);

	print_header();
	while (42)
	{
		get_cmd_signal();
		cmd = getCmd(&data);
		print_cmd(cmd);
		if (cmd)
			exec_cmds(cmd, cmd, &data);
		else
		{
			g_exit_status = 0;
			cmd_exit(cmd, cmd, &data); // gestion du ctrl + D
		}
		free_cmd(cmd);
	}
	exit_clean(&data, NULL);
	return (0);
}

