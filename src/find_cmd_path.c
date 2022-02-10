/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:45:29 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/10 18:40:04 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**find_path(t_list *env)
{
	char	*var_path;

	var_path = NULL;
	while (!var_path && env != NULL)
	{
		if (!ft_memcmp("PATH=", env->content, 5))
			var_path = env->content;
		env = env->next;
	}
	if (var_path == NULL)
		return (NULL);
	return (ft_split(var_path + 5, ':'));
}

static char	*find_cmd_path_with_name(char *cmd_name)
{
	if (is_a_file(cmd_name))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	ft_putstr_fd(cmd_name,2);
	ft_putstr_fd(": Is a directory", 2);
	return(NULL);
}

static char	*find_cmd_absolute_path(char *cmd_name, t_list* env)
{
	char	**path;
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	if (cmd_name && cmd_name[0] != '\0')
	{
		path = find_path(env);
		if (path == NULL)
			return (NULL);
		cmd_name = ft_strjoin("/", cmd_name);
		i = -1;
		while (cmd_name && !cmd_path && path[++i])
		{
			cmd_path = ft_strjoin(path[i], cmd_name);
			if (cmd_path && access(cmd_path, X_OK))
			{
				free(cmd_path);
				cmd_path = NULL;
			}
		}
		free(cmd_name);
		free_tab(path);
	}
	return (cmd_path);
}

char	*find_cmd_name(char **cmd)
{
	int	i = 0;
	
	while (cmd[i])
	{
		if (!ft_memcmp(cmd[i], "<", 2) || !ft_memcmp(cmd[i], "<<", 3)
			|| !ft_memcmp(cmd[i], ">", 2) || !ft_memcmp(cmd[i], ">>", 3))
			i++;
		else
			return (cmd[i]);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd, t_list *env)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = find_cmd_name(cmd);
	if (cmd_name = NULL)
		return (NULL);
	if (is_in_str(cmd_name, '/'))
		cmd_path = find_cmd_path_with_name(cmd_name);
	else
	{
		cmd_path = find_cmd_absolute_path(cmd_name, env);
		if (cmd_path == NULL)
		{
			ft_putstr_fd("Command not found: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putchar_fd('\n', 2);
		}
	}
	return (cmd_path);
}