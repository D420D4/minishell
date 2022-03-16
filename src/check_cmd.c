/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:30:51 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/16 16:30:52 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_parenthesis_left(char *s, int i)
{
	if (i == 0)
		return (0);
	if (s[i - 1] == ' ' || s[i - 1] == '(')
		return (check_parenthesis_left(s, i - 1));
	if (i > 1 && ((s[i - 1] == '&' && s[i - 2] == '&')
			|| (s[i - 1] == '|' && s[i - 2] == '|')))
		return (0);
	return (1);
}

static int	check_parenthesis_right(char *s, int i)
{
	if (i == ft_strlen(s) - 1)
		return (0);
	if (s[i + 1] == ' ' || s[i + 1] == ')')
		return (check_parenthesis_right(s, i + 1));
	if (i < ft_strlen(s) - 1 && ((s[i + 1] == '&' && s[i + 2] == '&')
			|| (s[i + 1] == '|' && s[i + 2] == '|')))
		return (0);
	return (1);
}

//Check if () are ok with && and ||
int	check_parenthesis(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (quote == 0 && s[i] == '(' && check_parenthesis_left(s, i))
			return (0);
		if (quote == 0 && s[i] == ')' && check_parenthesis_right(s, i))
			return (0);
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

int	check_syntax(char *brut)
{
	int	i;
	int	quote;
	int	nb_par;

	i = 0;
	nb_par = 0;
	quote = 0;
	while (brut[i] && nb_par >= 0)
	{
		if (!quote && brut[i] == '(')
			nb_par++;
		else if (!quote && brut[i] == ')')
			nb_par--;
		else if (brut[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (brut[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	if (nb_par != 0 || quote > 0)
		return (0);
	return (1);
}
