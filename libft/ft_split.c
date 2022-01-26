/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:51:43 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/09 02:35:14 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_next(char const *str, char c, int *i)
{
	int		d;
	int		f;
	char	*s;
	int		j;

	j = 0;
	while (*(str + j) == c && *(str + j))
		j++;
	if (!*(str + j))
		return (0);
	d = j;
	while (*(str + j) != c && *(str + j))
		j++;
	f = j;
	s = malloc (sizeof(char) * (f - d + 1));
	if (!s)
		return (0);
	j = -1;
	while (++j < f - d)
		*(s + j) = *(str + d + j);
	*(s + j) = 0;
	*i += f;
	return (s);
}

static int	ft_get_next_2(char const *str, char c, int *i)
{
	int		d;
	int		f;
	int		j;

	j = 0;
	while (*(str + j) == c && *(str + j))
		j++;
	if (!*(str + j))
		return (0);
	d = j;
	while (*(str + j) != c && *(str + j))
		j++;
	f = j;
	j = 0;
	while (j < f - d)
		j++;
	*i += f;
	return (1);
}

static char	**free_all(char **s, int n)
{
	while (n >= 0)
	{
		free (s[n]);
		n--;
	}
	free (s);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	int		nb;
	int		i;
	int		j;
	char	**s;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	while (ft_get_next_2(str + i, c, &i))
		nb++;
	s = (char **) malloc(sizeof(char *) * (nb + 1));
	if (!s)
		return (0);
	j = 0;
	i = 0;
	while (j < nb)
	{
		*(s + j) = ft_get_next(str + i, c, &i);
		if (!*(s + j))
			return (free_all(s, j - 1));
		j++;
	}
	*(s + nb) = 0;
	return (s);
}
