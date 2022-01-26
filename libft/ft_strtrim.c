/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:41:39 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/26 00:15:45 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_array(char const c, char const *arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
	{
		if (*(arr + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i;
	int		len;
	int		d;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = 0;
	while (*(s1 + i) && is_in_array(*(s1 + i), set))
		i++;
	d = i;
	while (*(s1 + i + len))
		len++;
	i += len - 1;
	while (is_in_array(*(s1 + i), set) && i > d && len--)
		i--;
	s = malloc(len + 1);
	if (!s)
		return (0);
	i = -1;
	s[len] = 0;
	while (++i < len)
		s[i] = s1[i + d];
	return (s);
}
