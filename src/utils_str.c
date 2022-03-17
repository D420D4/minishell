/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:46:12 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 17:07:48 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_str(char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

int	ft_strcmp_wildcards(char *s1, char *s2)
{
	char	c1;
	char	c2;

	c1 = 0;
	c2 = 0;
	while (c1 == c2 && *s1 && *s2)
	{
		c1 = s1[0];
		c2 = s2[0];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		s1++;
		s2++;
	}
	if (c1 == c2)
		return (s1[0] - s2[0]);
	return (c1 - c2);
}

int	ft_strcmp_export(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	is_only_space(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] != ' ')
			return (0);
	}
	return (1);
}
