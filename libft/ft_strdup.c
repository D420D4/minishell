/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:29:19 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/25 15:38:26 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;

	i = 0;
	while (*(s + i))
		i++;
	ss = (char *)malloc(sizeof(char) * (i + 1));
	if (!ss)
		return (0);
	while (i >= 0)
	{
		ss[i] = s[i];
		i--;
	}
	return (ss);
}
