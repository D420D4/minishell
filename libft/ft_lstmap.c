/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:06:20 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/25 23:59:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*tt;

	(void) del;
	if (!lst)
		return (0);
	tt = ft_lstnew(f(lst->content));
	if (!tt)
		return (0);
	t = tt;
	while (lst->next)
	{
		lst = lst->next;
		t->next = ft_lstnew(f(lst->content));
		if (!t->next)
			return (0);
		t = t->next;
	}
	return (tt);
}
