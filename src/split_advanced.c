/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_advanced.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:41:16 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 01:05:50 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_word_to_lst(char *string, char *c, t_list **mots)
{
	if (!string)
		return (0);
	if (ft_strlen(string))
	{
		ft_lstadd_back(mots, ft_lstnew(string));
		if (!ft_lstlast(*mots)->content)
			return (0);
	}
	else
	{
		free(string);
		if (!ft_memcmp(c, "|", 2))
			return (0);
	}
	return (1);
}

static char	**free_lst_return_tab(t_list **mots, char **ss)
{
	ft_lstclear(mots, &free);
	return (ss);
}

char	**split_advanced(char *s, char *c)
{
	t_list	*mots;
	char	**ss;
	int		i;
	int		d;
	int		quote;

	d = 0;
	quote = 0;
	mots = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if ((!ft_memcmp(s + i, c, ft_strlen(c)) || !s[i]) && quote == 0)
		{
			if (!add_word_to_lst(ft_substr(s, d, i - d), c, &mots))
				return (free_lst_return_tab(&mots, NULL));
			d = i + ft_strlen(c);
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
	}
	ss = list_to_tab(mots);
	return (free_lst_return_tab(&mots, ss));
}
