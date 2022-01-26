/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:06:20 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/25 23:52:53 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **begin_list, t_list *new)
{
	t_list	*tt;

	if (!*begin_list)
	{
		*begin_list = new;
		return ;
	}
	tt = *begin_list;
	while (tt->next)
		tt = tt->next;
	tt->next = new;
}
