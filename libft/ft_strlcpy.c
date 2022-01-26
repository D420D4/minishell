/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:19:27 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/05 19:12:06 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i + 1 < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (n > 0)
		dest[i] = 0;
	while (src[i])
		i++;
	return (i);
}
