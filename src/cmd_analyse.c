/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:55 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/16 16:19:06 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*free_0(char *ss)
{
	free(ss);
	return (0);
}

char	*transform(char *original, t_data *data)
{
	int		i;
	char	*ss;
	int		not_null;

	i = 0;
	not_null = 0;
	ss = original;
	if (!ss)
		return (0);
	while (ss[i])
	{
		if (ss[i] == '"' && ++not_null)
		{
			if (inner_quote_1(&ss, &i, data))
				return (free_0(ss));
		}
		else if (ss[i] == '\'' && ++not_null)
		{
			if (inner_quote_2(&ss, &i))
				return (free_0(ss));
		}
		else if (ss[i] == '$')
			do_var(&ss, &i, data);
		else
			i++;
	}
	if (ss[0] == '\0' && !not_null)
		return (free_0(ss));
	return (ss);
}
