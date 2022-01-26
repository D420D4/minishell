/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:32:47 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/11 13:07:59 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

t_list_buf	*lst_new(int fd)
{
	t_list_buf	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (0);
	new->fd = fd;
	new->p = 0;
	new->next = 0;
	new->res = 0;
	return (new);
}

t_list_buf	*lst_search(t_list_buf **list, int fd)
{
	t_list_buf	**l;

	l = list;
	while (*l)
	{
		if ((*l)->fd == fd)
			return (*l);
		l = &(*l)->next;
	}
	*l = lst_new(fd);
	return (*l);
}

void	lst_remove(t_list_buf **list, int fd)
{
	t_list_buf	*l;

	if (!list)
		return ;
	if ((*list)->fd == fd || fd == -1)
	{
		l = (*list)->next;
		free(*list);
		*list = l;
		return ;
	}
	lst_remove(&((*list)->next), fd);
}

char	*prolonge_malloc(char *s, int size)
{
	int		i;
	char	*ns;

	if (!s)
		return (malloc(size + 1));
	i = 0;
	while (s[i])
		i++;
	ns = malloc(i + size + 1);
	if (!ns)
		return (0);
	i = -1;
	while (s[++i])
		ns[i] = s[i];
	ns[i] = 0;
	free (s);
	return (ns);
}
