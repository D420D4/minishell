/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:32:37 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 18:09:16 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (0);
}

char	*get_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return (NULL);
	if (getcwd(pwd, 4096) == NULL)
	{
		perror("getcwd");
		free(pwd);
		return (NULL);
	}
	return (pwd);
}
