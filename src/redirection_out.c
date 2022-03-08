/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:09:58 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/08 20:37:55 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_new_rd_out_trunc(char *filename, int *rd_out)
{
	close_fd(*rd_out);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
}

void	set_new_rd_out_append(char *filename, int *rd_out)
{
	close_fd(*rd_out);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
}
