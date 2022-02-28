/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:54:05 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/28 14:56:24 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_size(int size, char **strs)
{
	int	i;
	int	total_size;

	i = -1;
	total_size = 0;
	while (++i < size)
		total_size += ft_strlen(strs[i]);
	return (total_size);
}

static int	ft_append_string(char *dest, char *src, int n)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[n + i] = src[i];
	return (i);
}

//LE RETOUR DU VRAI STRJOIN DU C7 TMTC
char	*ft_strjoin_vector(int size, char **strs, char *sep)
{
	int		total_size;
	char	*final_string;
	int		i;
	int		i_total;

	if (size <= 0)
		total_size = 0;
	else
		total_size = ft_count_size(size, strs) + ft_strlen(sep) * (size - 1);
	final_string = malloc((total_size + 1) * sizeof(char));
	if (final_string == NULL)
		return (NULL);
	i = 0;
	i_total = 0;
	while (size > 0 && i < size)
	{
		i_total += ft_append_string(final_string, strs[i], i_total);
		i++;
		if (i < size)
			i_total += ft_append_string(final_string, sep, i_total);
	}
	final_string[i_total] = '\0';
	return (final_string);
}
