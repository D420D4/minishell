/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:25:18 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/10 18:50:23 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_cmd_argv(char **cmd, char *cmd_path)
{
	char	**cmd_argv;
	int		i;
	int		len;

	len = 0;
	i = -1;
	while (cmd[++i])
	{
		if (!ft_memcmp(cmd[i], "<", 2) || !ft_memcmp(cmd[i], "<<", 3)
			|| !ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3))
			i++;
		else
			len++;
	}
	cmd_argv = malloc(sizeof(char *) * (len + 1));
	if (cmd_argv == NULL)
		return (NULL);
	i = -1;
	len = 0;
	while (cmd[++i])
	{
		if (!ft_memcmp(cmd[i], "<", 2) || !ft_memcmp(cmd[i], "<<", 3)
			|| !ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3))
			i++;
		else
		{
			if (len == 0)
				cmd_argv[len++] = ft_strdup(cmd[i]);
			else
				cmd_argv[len++] = ft_strdup(cmd_path);
		}
	}
	cmd_argv[len] = NULL;
	if (check_null(cmd_argv, len))
		return (NULL);
	return (cmd_argv);
}
