/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:16:39 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/26 00:08:11 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ss;

	if (!s)
		return (0);
	i = 0;
	while (*(s + i))
		i++;
	ss = malloc(i + 1);
	if (!ss)
		return (0);
	ss[i] = 0;
	if (!ss)
		return (0);
	i = 0;
	while (*(s + i))
	{
		ss[i] = (*f)(i, *(s + i));
		i++;
	}
	return (ss);
}
