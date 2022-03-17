/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:46:41 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 16:51:03 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_start_sequence(char *sequence, char **d_name, char **s, int i)
{
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len_sequence = ft_strlen(sequence);
	if (ft_memcmp(sequence, *d_name, len_sequence))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	*d_name = *d_name + len_sequence;
	*s = *s + i + 1;
	return (1);
}

int	check_end_sequence(char *sequence, char *d_name)
{
	int	len;
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(d_name);
	len_sequence = ft_strlen(sequence);
	if (len < len_sequence)
	{
		free(sequence);
		return (0);
	}
	if (ft_memcmp(sequence, d_name + len - len_sequence, len_sequence + 1))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	return (1);
}

int	check_first_wildards(char **s, char **d_name, t_data *data)
{
	int		i;
	int		quote;
	char	*sub;

	i = 0;
	quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '*' && !quote)
		{
			sub = transform(ft_substr(*s, 0, i), data);
			if (!check_start_sequence(sub, d_name, s, i))
				return (0);
			else
				return (1);
		}
		else if ((*s)[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if ((*s)[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

int	check_sequence(char *sequence, char **d_name)
{
	int		len;
	char	*search;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(*d_name);
	search = ft_strnstr(*d_name, sequence, len);
	if (search == NULL)
	{
		free(sequence);
		return (0);
	}
	*d_name = search + ft_strlen(sequence);
	free(sequence);
	return (1);
}
