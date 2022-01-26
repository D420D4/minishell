/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:34:53 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/24 20:08:51 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, int n)
{
	int	i;

	if (!dest && !src)
		return (0);
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			*((char *) dest + i) = *((char *) src + i);
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			*((char *) dest + n - i - 1) = *((char *) src + n - i - 1);
			i++;
		}
	}
	return (dest);
}
