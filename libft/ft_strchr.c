/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:23:36 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/30 15:25:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) && *((unsigned char *)(s + i)) != ((unsigned char) c))
		i++;
	if (*(s + i) || ((unsigned char) c == 0))
		return (s + i);
	return (0);
}
