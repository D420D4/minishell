/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:23:23 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/12 21:56:28 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static int	add_redirection(char *s, t_list **mots, int *i, int *d)
{
	char *string;

	string = ft_substr(s, *d, *i - *d);
	if (!string)
		return (0);
	if (is_only_space(string))
	{
		free(string);
		if (*mots != 0)
		{
			ft_putstr_fd("syntax error\n", 2);
			g_exit_status = 2;
			return (0);
		}
	}
	else
	{
		ft_lstadd_back(mots, ft_lstnew(string));
		if (!ft_lstlast(*mots)->content)
			return (0);
	}
	if (!ft_memcmp(s + *i, ">>", 2))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup(">>")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!ft_memcmp(s + *i, ">", 1))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup(">")));
		*d = *i + 1;
	}
	else if (!ft_memcmp(s + *i, "<<", 2))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup("<<")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!ft_memcmp(s + *i, "<", 1))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup("<")));
		*d = *i + 1;
	}
	else
		return (1);
	if (!ft_lstlast(*mots)->content)
		return (0);
	return (1);
}

char	**split_advanced_redirections(char *s)
{
	t_list *mots;
	char **ss;
	int i;
	int d;
	int quote;

	i = 0;
	d = 0;
	quote = 0;
	mots = 0;

	i = 0;
	while (i <= ft_strlen(s))
	{
//		printf("%s\n", s + i);

		if ((!s[i] || !ft_memcmp(s + i, ">>", 2) || !ft_memcmp(s + i, ">", 1)
			|| !ft_memcmp(s + i, "<<", 2) || !ft_memcmp(s + i, "<", 1)) && quote == 0)
		{
			//printf("[{%s}] %d\n", s + i, i);
			if (!add_redirection(s, &mots, &i, &d))
			{
				ft_lstclear(&mots, &free);
					return (0);
			}
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	ss = list_to_tab(mots);
	ft_lstclear(&mots,&free);
	return (ss);
}

char	**do_redirections(t_cmd *cmd, t_data *data)
{
	t_list	*mots;
	int	j;
	int	i;
	char	**ss;
	char	*string;
	char	**wildcards;

	char	**split = cmd->parsing_pre_analysis;
	mots = 0;
	i = -1;
	if (!cmd->parsing_pre_analysis)
		return (NULL);
	while(split[++i])
	{
		if (!ft_memcmp(split[i], ">>", 3))
		{
			if (!set_new_rd_out_append(split[i + 1], &(cmd->fd_out), data))
				return (NULL);
			i++;
		}
		else if (!ft_memcmp(split[i], ">", 2))
		{
			if (!set_new_rd_out_trunc(split[i + 1], &(cmd->fd_out), data))
				return (NULL);
			i++;
		}
		else if (!ft_memcmp(split[i], "<<", 3))
		{
			cmd->fd_in = cmd->fd_heredocs;
			i++;
		}
		else if (!ft_memcmp(split[i], "<", 2))
		{
			if (!set_new_rd_in_open(split[i + 1], &(cmd->fd_in), data))
				return (NULL);
			i++;
		}
		else
		{
			if (is_in_special('*', split[i]))
			{
				wildcards = do_wildcards_word(split[i], data);
				if (!wildcards || !wildcards[0])
					ft_lstadd_back(&mots, ft_lstnew(transform(ft_strdup(split[i]), data)));
				else
				{
					j = -1;
					while (wildcards[++j])
						ft_lstadd_back(&mots, ft_lstnew(ft_strdup(wildcards[j])));
				}
			}
			else
			{
				string = transform(ft_strdup(split[i]), data);
				if (string)
					ft_lstadd_back(&mots, ft_lstnew(string));
			}
		}
	}
	ss = list_to_tab(mots);
	ft_lstclear(&mots,&free);
	if (cmd->fd_in != cmd->fd_heredocs)
		close_fd(cmd->fd_heredocs);
	return (ss);
}
