/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:31:28 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/16 16:31:29 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	genious_quote(const char c, int quote)
{
	if (c == '\'' && quote != 2)
		quote = (quote + 1) % 2;
	else if (c == '\"' && quote != 1)
		quote = (quote + 2) % 4;
	return (quote);
}

static char	*do_start_parentese(const char *s, int *i, int j)
{
	int		nb_par;
	char	*cp;
	int		k;
	int		quote;

	nb_par = 1;
	quote = 0;
	while (s[++j] && nb_par)
	{
		if (!quote && s[j] == '(')
			nb_par++;
		if (!quote && s[j] == ')')
			nb_par--;
		quote = genious_quote(s[j], quote);
	}
	k = j;
	while (s[j] == ' ')
		j++;
	if (ft_memcmp(s + j, "&&", 2) && ft_memcmp(s + j, "||", 2) && s[j])
		return (0);
	cp = malloc(k - 1 - *i);
	memcpy(cp, s + 1 + *i, k - 2 - *i);
	cp[k - 2 - *i] = 0;
	*i = j;
	return (cp);
}

static char	*do_not_start_parentese(char *s, int *i, int j)
{
	int		quote;
	char	*cp;
	int		cmp;

	cmp = 0;
	quote = 0;
	while (s[j])
	{
		if (!ft_memcmp(s + j, "&&", 2) || !ft_memcmp(s + j, "||", 2))
		{
			*i = j;
			cmp++;
		}
		if (cmp == 2 || !s[j + 1])
		{
			j = *i;
			cp = malloc(j + 1);
			memcpy(cp, s, j);
			cp[j] = 0;
			return (cp);
		}
		quote = genious_quote(s[j++], quote);
	}
	return (0);
}

static char	*get_next(char *s, int *i)
{
	int		j;

	j = 0;
	while (s[j] == ' ')
		j++;
	*i = j;
	if (s[j] == '(')
		return (do_start_parentese(s, i, j));
	else
		return (do_not_start_parentese(s, i, j));
}

int	progress(t_cmd *cmd)
{
	int		i;
	char	*ncmd;
	char	*nncmd;

	i = 0;
	if (!cmd || !cmd->txt)
		return (0);
	if (is_finish(cmd->txt))
		return (0);
	ncmd = get_next(cmd->txt, &i);
	if (!ncmd)
		return (0);
	nncmd = strdup(cmd->txt + i + 2);
	if (cmd->txt[i] == '&')
		cmd->on_success = new_cmd_txt(nncmd);
	if (cmd->txt[i] == '|')
		cmd->on_fail = new_cmd_txt(nncmd);
	cmd->soon = new_cmd_txt(ncmd);
	progress(cmd->soon);
	progress(cmd->on_success);
	progress(cmd->on_fail);
	free(ncmd);
	free(nncmd);
	return (1);
}
