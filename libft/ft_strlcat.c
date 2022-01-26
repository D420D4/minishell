/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:11:42 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/09 04:28:43 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	s;
	unsigned int	len;

	i = 0;
	s = 0;
	len = (unsigned int) ft_strlen(dest);
	while (dest[s] && s < size)
		s++;
	while (src[i] && s + i + 1 < size)
	{
		dest[s + i] = src[i];
		i++;
	}
	if (size != 0 && size >= len)
		dest[s + i] = 0;
	if (size < len)
		return (ft_strlen(src) + size);
	return (ft_strlen(src) + len);
}
