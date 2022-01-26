/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:32:37 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/11 13:08:24 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static char	*quit(char *s, t_list_buf	**list, int i, int fd)
{
	lst_remove (list, fd);
	if (i == 0)
	{
		if (s)
			free (s);
		return (0);
	}
	return (s);
}

static void	init(t_list_buf *l, int fd)
{
	if (l->res == 0)
	{
		l->p = 0;
		l->res = read(fd, l->buff, BUFFER_SIZE);
	}
}

static char	*finalize(char *s, t_list_buf *l, int *i)
{
	s[*i] = '\n';
	*i = *i + 1;
	s[*i] = 0;
	l->p++;
	return (s);
}

static char	*clearall(t_list_buf **pListbuf)
{
	while (*pListbuf)
		lst_remove(pListbuf, -1);
	return (0);
}

char	*get_next_line(int fd)
{
	char				*s;
	static t_list_buf	*list = 0;
	t_list_buf			*l;
	int					i;

	if (fd < 0)
		return (clearall(&list));
	l = lst_search(&list, fd);
	init(l, fd);
	s = 0;
	i = 0;
	while (l->res)
	{
		s = prolonge_malloc(s, l->res);
		if (!s || l->res == -1)
			return (quit(s, &list, 0, fd));
		while (l->p < l->res && l->buff[l->p] != '\n')
			s[i++] = l->buff[l->p++];
		if (l->p < l->res)
			return (finalize(s, l, &i));
		l->res = read(fd, l->buff, BUFFER_SIZE);
		l->p = 0;
		s[i] = 0;
	}
	return (quit(s, &list, i, fd));
}
