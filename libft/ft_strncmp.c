/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:08:59 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/05 18:14:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char *)s1 + i)
		&& *((unsigned char *)s1 + i)
		== *((unsigned char *)s2 + i)
		&& i < n - 1)
		i++;
	return ((int)(*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i)));
}
