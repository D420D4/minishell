/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:23:36 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/01 19:37:01 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*ss;

	ss = 0;
	i = 0;
	while (*(s + i))
	{
		if (*((unsigned char *)(s + i)) == (unsigned char) c)
			ss = s + i;
		i++;
	}
	if (!(unsigned char) c)
		return (s + i);
	return (ss);
}
