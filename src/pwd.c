/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:32:37 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/19 16:16:05 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return (1);
	if (getcwd(pwd,4096) == NULL)
	{
		perror("getcwd");
		free(pwd);
		return (1);
	}
	ft_putendl_fd(pwd, cmd->fd_out);
	return (0);
}
