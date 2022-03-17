/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:16:01 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 00:38:50 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	do_heredocs(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int		i;
	char	**split;

	split = cmd->parsing_pre_analysis;
	if (!split)
		return (1);
	i = -1;
	while (split[++i])
	{
		if (!ft_memcmp(split[i], "<<", 3))
		{
			if (!set_new_rd_in_heredoc(split[i + 1], cmd, cmd_parent, data))
				return (0);
			i++;
		}
	}
	return (1);
}

static char	**split_redirections_and_space(char *bruts)
{
	char	**split;
	char	*new_brut;

	split = split_advanced_redirections(bruts);
	if (!split)
		return (NULL);
	new_brut = ft_strjoin_vector(len_tab(split), split, " ");
	free_tab(split);
	if (!new_brut)
		return (0);
	split = split_advanced(new_brut, " ");
	free(new_brut);
	return (split);
}

static int	preparse_line_no_pipe(t_cmd **cmd, char **bruts,
			t_cmd *cmd_parent, t_data *data)
{
	char	**split;

	if (!bruts)
		return (0);
	if (!*bruts)
		return (1);
	if (is_only_space(*bruts))
		return (0);
	if (!*cmd)
		*cmd = new_cmd();
	split = split_redirections_and_space(*bruts);
	if (!split)
		return (0);
	(*cmd)->parsing_pre_analysis = split;
	if (!do_heredocs(*cmd, cmd_parent, data))
		return (-1);
	return (preparse_line_no_pipe(&((*cmd)->pipe),
			bruts + 1, cmd_parent, data));
}

int	preparse_line(t_cmd **cmd, char *brut, t_cmd *cmd_parent, t_data *data)
{
	char	**bruts;
	int		ret;

	bruts = split_advanced(brut, "|");
	cmd_parent->bruts = bruts;
	ret = preparse_line_no_pipe(cmd, bruts, cmd_parent, data);
	free_tab(bruts);
	cmd_parent->bruts = NULL;
	if (ret != 1)
		return (ret);
	return (1);
}
