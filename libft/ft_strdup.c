/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:29:19 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/08 15:33:02 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;

	i = 0;
	if (!s)
		return (NULL);
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
