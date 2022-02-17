/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:32:37 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/16 15:37:36 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(void)
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
	ft_putendl_fd(pwd, 1);
	return (0);
}
