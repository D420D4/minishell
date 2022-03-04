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
	data.env = parse_env(envp);
	while (42)
	{
		getCmdSignal();
		cmd = getCmd(&data);
		print_cmd(cmd);
		if (cmd)
			exec_cmd(cmd, &data);
		else
		{
			g_exit_status = 0;
			cmd_exit(cmd, &data); // gestion du ctrl + D
		}
		free_cmd(cmd);
	}
	ft_lstclear(&data.env, &free);
	exit_clean();
	return (0);
}

