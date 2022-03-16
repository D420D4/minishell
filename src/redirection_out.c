/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:09:58 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/16 16:37:53 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_filename(char *filename_brut, t_data *data)
{
	char	**wildcards;
	char	*filename;

	if (is_in_special('*', filename_brut))
	{
		wildcards = do_wildcards_word(filename_brut, data);
		if (!wildcards || len_tab(wildcards) > 1)
			filename = NULL;
		else if (wildcards[0] == 0)
			filename = transform(ft_strdup(filename_brut), data);
		else
			filename = ft_strdup(wildcards[0]);
		free_tab(wildcards);
	}
	else
		filename = transform(ft_strdup(filename_brut), data);
	return (filename);
}

int	set_new_rd_out_trunc(char *filename_brut, int *rd_out, t_data *data)
{
	char	*filename;

	close_fd(*rd_out);
	filename = find_filename(filename_brut, data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		free(filename);
		g_exit_status = 1;
		ft_putstr_fd("ambiguous redirect\n", 2);
		*rd_out = -1;
		return (0);
	}
	free(filename);
	return (1);
}

int	set_new_rd_out_append(char *filename_brut, int *rd_out, t_data *data)
{
	char	*filename;

	close_fd(*rd_out);
	filename = find_filename(filename_brut, data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		free(filename);
		g_exit_status = 1;
		ft_putstr_fd("ambiguous redirect\n", 2);
		*rd_out = -1;
		return (0);
	}
	free(filename);
	return (1);
}
