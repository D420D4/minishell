/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:32:58 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/06 21:45:09 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int nmemb, unsigned int size)
{
	void				*c;
	unsigned int		i;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (0);
	if (!(nmemb && size))
		return (malloc(1));
	c = malloc(size * nmemb);
	if (!c)
		return (0);
	i = 0;
	while (i < size * nmemb)
		*((unsigned char *) c + i++) = 0;
	return (c);
}
