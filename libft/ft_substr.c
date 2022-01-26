/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:55:43 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/05 19:04:30 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_0(void)
{
	char	*ss;

	ss = malloc(1);
	if (!ss)
		return (0);
	ss[0] = 0;
	return (ss);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ss;
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < start)
		if (!*(s + i++))
			return (return_0());
	i = 0;
	while (i < len && s[start + i])
		i++;
	ss = malloc(i + 1);
	if (!ss)
		return (0);
	ss[i] = 0;
	i = 0;
	while (i < len && *(s + i + start))
	{
		*(ss + i) = *(s + start + i);
		i++;
	}
	return (ss);
}
