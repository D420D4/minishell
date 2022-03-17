/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:42:35 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 13:43:12 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	argument_is_n(char **args, int *i)
{
	int	j;
	int	end;

	*i = 1;
	end = 1;
	while (end && args[*i])
	{
		if (args[*i][0] == '-')
		{
			j = 1;
			while (args[*i][j] == 'n')
				j++;
			if (!args[*i][j] && j > 1)
				(*i)++;
			else
				end = 0;
		}
		else
			end = 0;
	}
	if (*i > 1)
		return (1);
	return (0);
}

int	cmd_echo(t_cmd *cmd)
{
	int	n;
	int	i;

	n = argument_is_n(cmd->cmd, &i);
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i++], cmd->fd_out);
		if (cmd->cmd[i])
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (!n)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
