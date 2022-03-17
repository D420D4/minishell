/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:04:21 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 00:12:55 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_color(char **line)
{
	char	*temp;

	temp = *line;
	if (g_exit_status)
		*line = ft_strjoin("\e[1;31m➜\e[1;36m minishell: \e[1;34m", temp);
	else
		*line = ft_strjoin("\e[1;32m➜\e[1;36m minishell: \e[1;34m", temp);
	free(temp);
	temp = *line;
	*line = ft_strjoin(temp, " $> \e[0m");
	free(temp);
}

static int	get_startingline(char **line, t_data *data)
{
	char	*pwd;
	char	*home;

	pwd = get_pwd();
	if (pwd == NULL)
		return (0);
	home = getvalue("HOME", data);
	if (home && !ft_memcmp(pwd, home, ft_strlen(home)))
	{
		*line = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
	}
	else
		*line = pwd;
	add_color(line);
	if (*line == NULL)
		return (0);
	return (1);
}

t_cmd	*get_cmd(t_data *data)
{
	char	*startingline;
	char	*brut;
	t_cmd	*cmd;

	cmd = 0;
	if (!get_startingline(&startingline, data))
		return (0);
	brut = readline(startingline);
	free(startingline);
	if (!brut)
		return (0);
	if (!is_only_space(brut))
		add_history(brut);
	parse_group(&cmd, brut, data);
	free(brut);
	return (cmd);
}
