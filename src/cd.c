/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:31:34 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 13:38:44 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	changepwd(t_data *data)
{
	t_list	*lst;
	char	*pwd;
	char	*new_content;

	lst = data->env;
	while (lst)
	{
		if (!ft_memcmp("PWD=", (char *) lst->content, 4))
		{
			pwd = get_pwd();
			if (pwd == NULL)
				return ;
			new_content = ft_strjoin("PWD=", pwd);
			free(pwd);
			if (new_content == NULL)
				return ;
			free(lst->content);
			lst->content = new_content;
			return ;
		}
		lst = lst->next;
	}
}

static char	*find_abolute_path(char *path, t_data *data)
{
	char	*home;
	char	*pwd;
	char	*temp;

	if (path == NULL)
	{
		home = getvalue("HOME", data);
		if (home == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		return (ft_strdup(home));
	}
	else if (!is_in_str(path, '/'))
	{
		path = ft_strjoin("/", path);
		if (path == NULL)
			return (NULL);
		pwd = get_pwd();
		temp = ft_strjoin(pwd, path);
		free(path);
		free(pwd);
		return (temp);
	}
	return (ft_strdup(path));
}

static int	print_cd_error(char *absolute_path, char *path)
{
	if (access(absolute_path, F_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	else if (is_a_file(absolute_path))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	else if (access(absolute_path, X_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int	cmd_cd(char **cmd, t_data *data)
{
	char	*absolute_path;

	if (cmd == NULL || (cmd[1] != NULL && cmd[2] != NULL))
	{
		ft_putendl_fd("cd : too many arguments", 2);
		return (1);
	}
	absolute_path = find_abolute_path(cmd[1], data);
	if (absolute_path == NULL || print_cd_error(absolute_path, cmd[1]))
	{
		free(absolute_path);
		return (1);
	}
	if (chdir(absolute_path))
	{
		perror("chdir");
		free(absolute_path);
		return (1);
	}
	free(absolute_path);
	changepwd(data);
	return (0);
}
