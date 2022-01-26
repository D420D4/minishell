/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:06:20 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/05 18:11:53 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **begin_list, void (*del)(void *))
{
	t_list	*t;
	t_list	*lst;

	lst = *begin_list;
	while (lst)
	{
		t = lst->next;
		if (lst->content)
			del(lst->content);
		free(lst);
		lst = t;
	}
	*begin_list = 0;
}
