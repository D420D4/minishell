/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:32:37 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 13:44:25 by lcalvie          ###   ########.fr       */
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
