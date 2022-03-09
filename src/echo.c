//
// Created by plefevre on 2/11/22.
//
#include "../includes/minishell.h"

int	cmd_echo(t_cmd *cmd)
{
	int n;
	int i;
	char **av;
	
	av = cmd->cmd;
	n = 0;
	if (av && av[0] && av[1])
		n = !ft_memcmp(av[1], "-n", 3);
	av += 1 + n;
	i = 0;
	if (av)
	{
		while (av[i])
		{
			ft_putstr_fd(av[i++], cmd->fd_out);
			if (av[i])
				ft_putstr_fd(" ", cmd->fd_out);
		}
	}
	if (!n)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}