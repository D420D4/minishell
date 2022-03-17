/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:55 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/17 00:01:14 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*free_0(char *ss)
{
	free(ss);
	return (0);
}

static int	need_transform(char **ss, int *i, t_data *data, int *not_null)
{
	if ((*ss)[*i] == '"' && ++(*not_null))
	{
		if (inner_quote_1(ss, i, data))
			return (2);
	}
	else if ((*ss)[*i] == '\'' && ++(*not_null))
	{
		if (inner_quote_2(ss, i))
			return (2);
	}
	else if ((*ss)[*i] == '$')
		do_var(ss, i, data);
	else
		return (0);
	return (1);
}

char	*transform(char *original, t_data *data)
{
	int		i;
	int		j;
	char	*ss;
	int		not_null;

	i = 0;
	not_null = 0;
	ss = original;
	if (!ss)
		return (0);
	while (ss[i])
	{
		j = need_transform(&ss, &i, data, &not_null);
		if (j == 2)
			return (free_0(ss));
		else if (j == 0)
			i++;
	}
	if (ss[0] == '\0' && !not_null)
		return (free_0(ss));
	return (ss);
}
