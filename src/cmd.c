/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:42:35 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 00:42:48 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe = 0;
	cmd->on_success = 0;
	cmd->on_fail = 0;
	cmd->soon = 0;
	cmd->cmd = 0;
	cmd->txt = 0;
	cmd->cmd_path = 0;
	cmd->parsing_pre_analysis = 0;
	cmd->pipe = 0;
	cmd->fd_heredocs = -1;
	cmd->bonus = 0;
	return (cmd);
}

t_cmd	*new_cmd_txt(char *txt)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (0);
	cmd->txt = ft_strdup(txt);
	cmd->bonus = !(is_finish(txt));
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->pipe)
		free_cmd(cmd->pipe);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd)
		free_tab(cmd->cmd);
	if (cmd->txt)
		free(cmd->txt);
	if (cmd->soon)
		free_cmd(cmd->soon);
	if (cmd->parsing_pre_analysis)
		free_tab(cmd->parsing_pre_analysis);
	close_fd(cmd->fd_heredocs);
	if (cmd->on_fail)
		free_cmd(cmd->on_fail);
	if (cmd->on_success)
		free_cmd(cmd->on_success);
	free(cmd);
}
