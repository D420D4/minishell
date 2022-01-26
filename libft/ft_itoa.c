/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:58:17 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/25 23:52:29 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	i;
	int	nn;

	nn = n;
	i = 0;
	if (n == 0)
		return (1);
	while (nn != 0)
	{
		nn /= 10;
		i++;
	}
	return (i + (n < 0));
}

char	*ft_itoa(int n)
{
	int		t;
	char	*s;

	t = get_len(n);
	s = malloc(t + 1);
	if (!s)
		return (s);
	s[t--] = 0;
	if (n == 0)
		s[t--] = '0';
	while (n != 0)
	{
		s[t--] = '0' + ((n % 10) * (-1 + 2 * (n > 0)));
		n /= 10;
	}
	if (t == 0)
		s[0] = '-';
	return (s);
}
