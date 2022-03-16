/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_no_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:54:20 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/16 16:00:06 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	len_no_quote(char *limiter_brut)
{
	int	len;
	int	quote;
	int	i;

	i = -1;
	len = 0;
	quote = 0;
	while (limiter_brut[++i])
	{
		if (limiter_brut[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (limiter_brut[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			len++;
	}
	return (len);
}

char	*ft_strdup_no_quote(char *limiter_brut)
{
	char	*limiter;
	int		i;
	int		j;
	int		quote;

	if (!limiter_brut)
		return (NULL);
	limiter = malloc(sizeof(char) * (len_no_quote(limiter_brut) + 1));
	if (!limiter)
		return (NULL);
	i = -1;
	j = -1;
	quote = 0;
	while (limiter_brut[++i])
	{
		if (limiter_brut[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (limiter_brut[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			limiter[++j] = limiter_brut[i];
	}
	limiter[++j] = '\0';
	return (limiter);
}
