/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:06:16 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/09 01:27:55 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	read_stdin(char *limiter, int fd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	line = readline("> ");
	while (line && ft_memcmp(line,limiter, len + 1))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
	{
		ft_putstr_fd("Warning : here-document delemited by end-of-file ( wanted `", 1);
		ft_putstr_fd(limiter, 1);
		ft_putstr_fd("\' )\n", 1);
	}
}

void	set_new_rd_in_open(char *filename, int *rd_in)
{
	close_fd(*rd_in);
	if (filename)
	{
		*rd_in = open(filename, O_RDONLY);
		if (*rd_in == -1)
			perror("open");
	}
}

int	set_new_rd_in_heredoc(char *limiter, int *rd_in)
{
	int	pid;
	int	pipefds[2];
	int	status;

	close_fd(*rd_in);
	if (limiter)
	{
		if (pipe(pipefds) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			close_fd(pipefds[0]);
			if (signal(SIGINT, SIG_DFL) == SIG_ERR)
				printf("failed to register interrupts with kernel\n");
			read_stdin(limiter,pipefds[1]);
			exit (0);
		}
		nothingSignal();
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
		getCmdSignal();
		close_fd(pipefds[1]);
		if (__WIFSIGNALED(status) && WTERMSIG(status) == 2)
		{
			close_fd(pipefds[0]);
			ft_putstr_fd("\n", 1);
			g_exit_status = 130;
			return (0);
		}
		*rd_in = pipefds[0];
		return (1);
	}
	return (0);
}
