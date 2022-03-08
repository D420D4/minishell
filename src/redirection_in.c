/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:06:16 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/08 20:54:36 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//faut que je gere les signaux si ctrl+D ou ctrl+C dans les heredoc , jfais ca demain
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

void	set_new_rd_in_heredoc(char *limiter, int *rd_in)
{
	close_fd(*rd_in);
	if (limiter)
		*rd_in = read_stdin(limiter);
}
