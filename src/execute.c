/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:32:36 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/10 18:45:22 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	exec_cmd(t_cmd *cmd, t_data data)
{
	int	rd_in;
	int	rd_out;
	char	*cmd_path;
	char	**cmd_argv;

	while(cmd)
	{
		if (find_rd_in(cmd->cmd, &rd_in) || find_rd_output(cmd->cmd, &rd_out))
			return (1);
		if (rd_in != -1)
			cmd->fd_in = rd_in;
		if (rd_out != -1)
			cmd->fd_out = rd_out;
		cmd_path = find_cmd_path(cmd, data.env);
		cmd_argv = find_cmd_argv(cmd, cmd_path);
	}
	return (0);
}