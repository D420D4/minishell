/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:01:38 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/16 20:34:24 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_before_signal(int mode, int fd, char *limiter)
{
	static int		fd_save;
	static char		*limiter_save;

	if (mode == 1)
	{
		fd_save = fd;
		limiter_save = limiter;
	}
	else
	{
		close_fd(fd_save);
		free(limiter_save);
		fd_save = -1;
		limiter_save = NULL;
	}
}

void	quit_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		save_before_signal(0, 0, NULL);
		rl_clear_history();
		close(0);
		close(1);
		close(2);
		exit(130);
	}
}
