/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:34:16 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/05 18:35:23 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	s;
	size_t	i;

	if (!*to_find)
		return ((char *)str);
	s = 0;
	while (*(str + s) && s < len)
	{
		i = 0;
		while (*(to_find + i)
			&& *(to_find + i) == *(str + i + s) && s + i < len)
			i++;
		if (!*(to_find + i))
			return ((char *)(str + s));
		s++;
	}	
	return (0);
}
