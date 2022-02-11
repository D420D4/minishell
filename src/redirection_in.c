/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:06:16 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/11 13:19:51 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_stdin(char *limiter)
{
	char	*line;
	int		len;
	int		pipefds[2];

	if (pipe(pipefds) == -1)
			perror("pipe");
	len = ft_strlen(limiter);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	while (line
		&& !(ft_strncmp(line, limiter, len) == 0
			&& ft_strlen(line) == len + 1
			&& line[len] == '\n'))
	{
		ft_putstr_fd(line, pipefds[1]);
		free(line);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close_fd(pipefds[1]);
	return (pipefds[0]);
}

static int	set_new_rd_in_open(char *filename, int *rd_in)
{
	close_fd(*rd_in);
	if (filename)
	{
		*rd_in = open(filename, O_RDONLY);
		if (*rd_in == -1)
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

static int	set_new_rd_in_heredoc(char *limiter, int *rd_in)
{
	close_fd(*rd_in);
	if (limiter)
		*rd_in = read_stdin(limiter);
	else
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	find_rd_in(char **cmd, int *rd_in)
{
	int	i;

	*rd_in = -1;
	i = 0;
	while(cmd[i])
	{
		if (!ft_memcmp(cmd[i], "<", 2))
		{
			if (set_new_rd_in_open(cmd[i + 1], rd_in))
				return (1);
			i++;
		}
		else if (!ft_memcmp(cmd[i], "<<", 3))
		{
			if (set_new_rd_in_heredoc(cmd[i + 1], rd_in))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}