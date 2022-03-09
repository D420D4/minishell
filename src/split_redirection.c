/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:23:23 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/09 01:21:50 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static int	is_only_space(char *string)
{
	int i;

	i = -1;
	while (string[++i])
	{
		if (string[i] != ' ')
			return (0);
	}
	return (1);
}

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
	if (!memcmp(s + *i, ">>", 2))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup(">>")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!memcmp(s + *i, ">", 1))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup(">")));
		*d = *i + 1;
	}
	else if (!memcmp(s + *i, "<<", 2))
	{
		ft_lstadd_back(mots, ft_lstnew(ft_strdup("<<")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!memcmp(s + *i, "<", 1))
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
		if ((!s[i] || !memcmp(s + i, ">>", 2) || !memcmp(s + i, ">", 1) 
			|| !memcmp(s + i, "<<", 2) || !memcmp(s + i, "<", 1)) && quote == 0)
		{
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

char	**do_redirections(char **split, t_cmd *cmd)
{
	t_list	*mots;
	int	i;
	char	**ss;

	mots = 0;
	i = -1;
	while(split[++i])
	{
		if (!ft_memcmp(split[i], ">>", 3))
		{
			set_new_rd_out_append(split[i + 1], &(cmd->fd_out));
			i++;
		}
		else if (!ft_memcmp(split[i], ">", 2))
		{
			set_new_rd_out_trunc(split[i + 1], &(cmd->fd_out));
			i++;
		}
		else if (!ft_memcmp(split[i], "<<", 3))
		{
			if (!set_new_rd_in_heredoc(split[i + 1], &(cmd->fd_in)))
			{
				ft_lstclear(&mots,&free);
				return (NULL);
			}
			i++;
		}
		else if (!ft_memcmp(split[i], "<", 2))
		{
			set_new_rd_in_open(split[i + 1], &(cmd->fd_in));
			i++;
		}
		else
		{
			ft_lstadd_back(&mots, ft_lstnew(ft_strdup(split[i])));
			if (!ft_lstlast(mots)->content)
			{
				ft_lstclear(&mots,&free);
				return (0);
			}
		}
	}
	ss = list_to_tab(mots);
	ft_lstclear(&mots,&free);
	return (ss);
}
