/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:09:58 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/10 13:56:01 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int set_new_rd_out_trunc(char *filename, int *rd_out)
{
	if (*rd_out != -1)
		if (close(*rd_out))
			perror("close");
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static int set_new_rd_out_append(char *filename, int *rd_out)
{
	if (*rd_out != -1)
		if (close(*rd_out))
			perror("close");
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	find_rd_output(char **cmd, int *rd_out)
{
	int	i;

	i = 0;
	*rd_out = -1;
	while(cmd[i])
	{
		if (!ft_memcmp(cmd[i], ">", 2))
		{
			if (set_new_rd_out_trunc(cmd[i + 1], rd_out))
				return (1);
			i++;
		}
		else if (!ft_memcmp(cmd[i], ">>", 3))
		{
			if (set_new_rd_out_append(cmd[i + 1], rd_out))
				return (1);
			i++;
		}
		i++;
	}

	//TODO jai ajoute ca, faut peut etre mettre autre chose...
	return (0);
}