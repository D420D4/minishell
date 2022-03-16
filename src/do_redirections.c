/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:20:59 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/16 16:40:30 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	spread_words(t_cmd *cmd, int i, t_data *data)
{
	char	**split;

	split = cmd->parsing_pre_analysis;
	if (!ft_memcmp(split[i], ">>", 3))
		return (set_new_rd_out_append(split[i + 1], &(cmd->fd_out), data));
	else if (!ft_memcmp(split[i], ">", 2))
		return (set_new_rd_out_trunc(split[i + 1], &(cmd->fd_out), data));
	else if (!ft_memcmp(split[i], "<<", 3))
	{
		close_fd(cmd->fd_in);
		cmd->fd_in = cmd->fd_heredocs;
		return (1);
	}
	else if (!ft_memcmp(split[i], "<", 2))
		return (set_new_rd_in_open(split[i + 1], cmd, data));
	return (2);
}

static void	add_word_tranform(char *word, t_list **mots, t_data *data)
{
	char	**wildcards;
	char	*string;
	int		j;

	if (is_in_special('*', word))
	{
		wildcards = do_wildcards_word(word, data);
		if (!wildcards || !wildcards[0])
			ft_lstadd_back(mots,
				ft_lstnew(transform(ft_strdup(word), data)));
		else
		{
			j = -1;
			while (wildcards[++j])
				ft_lstadd_back(mots,
					ft_lstnew(ft_strdup(wildcards[j])));
		}
		free_tab(wildcards);
	}
	else
	{
		string = transform(ft_strdup(word), data);
		if (string)
			ft_lstadd_back(mots, ft_lstnew(string));
	}
}

static char	**create_cmd_tab(t_list *mots, t_cmd *cmd)
{
	char	**tab;

	tab = list_to_tab(mots);
	ft_lstclear(&mots, &free);
	if (cmd->fd_in == cmd->fd_heredocs)
		cmd->fd_heredocs = -1;
	return (tab);
}

char	**do_redirections(t_cmd *cmd, t_data *data)
{
	t_list	*mots;
	int		value;
	int		i;
	char	**split;

	split = cmd->parsing_pre_analysis;
	mots = 0;
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		value = spread_words(cmd, i, data);
		if (value == 0)
		{
			ft_lstclear(&mots, &free);
			return (NULL);
		}
		else if (value == 1)
			i++;
		else
			add_word_tranform(split[i], &mots, data);
	}
	return (create_cmd_tab(mots, cmd));
}
