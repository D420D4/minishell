/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:32:01 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/26 00:07:52 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !s2)
		return (0);
	len1 = 0;
	len2 = 0;
	i = -1;
	while (*(s1 + len1))
		len1++;
	while (*(s2 + len2))
		len2++;
	s = malloc(len1 + len2 + 1);
	if (!s)
		return (0);
	s[len1 + len2] = 0;
	while (*(s1 + ++i))
		*(s + i) = *(s1 + i);
	i--;
	while (*(s2 + ++i - len1))
		*(s + i) = *(s2 + i - len1);
	return (s);
}
