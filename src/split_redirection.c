/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:23:23 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/16 14:51:42 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_redirections(char *s, t_list **mots, int *i, int *d)
{
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
		return (0);
	return (1);
}

static int	add_word(char *s, t_list **mots, int *i, int *d)
{
	char	*string;

	string = ft_substr(s, *d, *i - *d);
	if (!string)
		return (0);
	if (is_only_space(string))
	{
		free(string);
		if (*mots != 0)
			return (0);
	}
	else
	{
		ft_lstadd_back(mots, ft_lstnew(string));
		if (!ft_lstlast(*mots)->content)
			return (0);
	}
	if (add_redirections(s, mots, i, d) && !ft_lstlast(*mots)->content)
		return (0);
	return (1);
}

static int	is_a_redirection(char *s)
{
	if (!ft_memcmp(s, ">>", 2) || !ft_memcmp(s, ">", 1))
		return (1);
	else if (!ft_memcmp(s, "<<", 2) || !ft_memcmp(s, "<", 1))
		return (1);
	else
		return (0);
}

static char	**create_preparsing_tab(t_list *mots)
{
	char	**tab;

	tab = list_to_tab(mots);
	ft_lstclear(&mots, &free);
	return (tab);
}

char	**split_advanced_redirections(char *s)
{
	t_list	*mots;
	int		i;
	int		d;
	int		quote;

	d = 0;
	quote = 0;
	mots = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if ((!s[i] || is_a_redirection(s + i)) && quote == 0)
		{
			if (!add_word(s, &mots, &i, &d))
			{
				ft_lstclear(&mots, &free);
				return (NULL);
			}
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
	}
	return (create_preparsing_tab(mots));
}
