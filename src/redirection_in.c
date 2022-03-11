/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:06:16 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/11 13:19:21 by lcalvie          ###   ########.fr       */
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

int	set_new_rd_in_open(char *filename_brut, int *rd_in, t_data *data)
{
	char *filename;
	char	**wildcards;
	
	close_fd(*rd_in);
	if (is_in_special('*', filename_brut))
	{
		wildcards = do_wildcards_word(filename_brut, data);
		if (!wildcards || len_tab(wildcards) > 1)
			filename = NULL;
		else if (wildcards[0] == 0)
			filename = filename_brut;
		else
			filename = wildcards[0];
	}
	else
		filename = transform(ft_strdup(filename_brut), data);
	if (filename)
	{
		*rd_in = open(filename, O_RDONLY);
		if (*rd_in == -1)
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

char	*no_quote(char *limiter_brut)
{
	char	*limiter;
	int	i;
	int	len;
	int	quote;

	if (!limiter_brut)
		return (NULL);
	i = -1;
	len = 0;
	while (limiter_brut[++i])
	{
		if (limiter_brut[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (limiter_brut[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			len++;
	}
	limiter = malloc(sizeof(char) * (len + 1));
	if (!limiter)
		return (NULL);
	i = -1;
	len = -1;
	while (limiter_brut[++i])
	{
		if (limiter_brut[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (limiter_brut[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			limiter[++len] = limiter_brut[i];
	}
	limiter[++len] = '\0';
	return (limiter);

}

int	set_new_rd_in_heredoc(char *limiter_brut, t_cmd *cmd)
{
	int	pid;
	int	pipefds[2];
	int	status;
	char	*limiter;

	close_fd(cmd->fd_heredocs);
	limiter = no_quote(limiter_brut);
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
		else
		{
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
			cmd->fd_heredocs = pipefds[0];
			return (1);
		}
	}
	return (0);
}
