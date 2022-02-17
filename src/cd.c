/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:31:34 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/17 19:07:41 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_cd(char **cmd, t_data *data)
{
	char	*absolut_path;
	char	*path;
	char	*home;
	char	*pwd;

	if (cmd == NULL || (cmd[1] != NULL && cmd[2] != NULL))
	{
		ft_putendl_fd("cd : too many arguments", 2);
		return (1);
	}
	if (cmd[1] == NULL)
	{
		home = getvalue("HOME", data);
		if (home == NULL)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
		absolut_path = ft_strdup(home);
		if (absolut_path == NULL)
			return (1);
	}
	else
	{
		path = cmd[1];
		if (cmd[1][0] == '~')
		{
			home = getvalue("HOME", data);
			if (home == NULL)
			{
				ft_putendl_fd("cd: HOME not set", 2);
				return (1);
			}
			absolut_path = ft_strjoin(home, cmd[1] + 1);
			if (absolut_path == NULL)
				return (1);
		}
		else if (!is_in_str(path, '/'))
		{
			path = ft_strjoin("/", path);
			if (path == NULL)
				return (1);
			pwd = malloc(sizeof(char) * 4096);
			if (pwd == NULL)
				return (1);
			if (getcwd(pwd,4096) == NULL)
			{
				perror("getcwd");
				free(pwd);
				return (1);
			}
			absolut_path = ft_strjoin(pwd, path);
			free(pwd);
			if (absolut_path == NULL)
				return (1);
		}
		else
			absolut_path = ft_strdup(path);
	}
	if (access(absolut_path, F_OK))
	{
		ft_putstr_fd("cd: ",2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(absolut_path);
		return (1);
	}
	if (is_a_file(absolut_path))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		free(absolut_path);
		return (1);
	}
	if (access(absolut_path, X_OK))
	{
		ft_putstr_fd("cd: ",2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(absolut_path);
		return (1);
	}
	if (chdir(absolut_path))
	{
		perror("chdir");
		free(absolut_path);
		return (1);
	}
	free(absolut_path);
	return (0);
}
