/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:18:27 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 17:06:05 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//remove "\0" element
char	**list_to_tab(t_list *lst)
{
	int		i;
	char	**ss;

	ss = malloc(sizeof (char *) * (len_cmd(lst) + 1));
	if (!ss)
		return (0);
	i = 0;
	while (lst)
	{
		if (((char *) lst->content) != NULL)
		{
			ss[i++] = ft_strdup((char *) lst->content);
			if (!ss[i - 1])
			{
				free_tab(ss);
				return (0);
			}
		}
		lst = lst->next;
	}
	ss[i] = 0;
	return (ss);
}

int	len_tab(char **tab)
{
	int	size;

	if (!tab)
		return (0);
	size = 0;
	while (tab[size])
		size++;
	return (size);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_sort_tab(char **tab, int size, int (f)(char *, char *))
{
	int		i;
	int		j;
	char	*str_temp;

	if (size <= 1)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (f(tab[i], tab[j]) < 0)
			{
				str_temp = &(tab[i][0]);
				tab[i] = &(tab[j][0]);
				tab[j] = str_temp;
			}
			j++;
		}
		i++;
	}
}
