/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:09:58 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/09 16:11:01 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_new_rd_out_trunc(char *filename_brut, int *rd_out, t_data *data)
{
	char	*filename;

	close_fd(*rd_out);
	filename = transform(ft_strdup(filename_brut), data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}

int	set_new_rd_out_append(char *filename_brut, int *rd_out, t_data *data)
{
	char	*filename;
	
	close_fd(*rd_out);
	filename = transform(ft_strdup(filename_brut), data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		g_exit_status = 1;
		ft_putstr_fd("ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}
