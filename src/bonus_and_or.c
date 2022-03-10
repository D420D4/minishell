//
// Created by plefevre on 3/8/22.
//

#include "../includes/minishell.h"


int is_finish(char *txt)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (txt[i]==' ')
		i++;
	if (txt[i] == '(')
		return (0);
	while (txt[i])
	{
		if(!quote && txt[i] == '&'  && txt[i + 1] == '&')
			return (0);
		if(!quote && txt[i] == '|'  && txt[i + 1] == '|')
			return (0);
		if (txt[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (txt[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

char	*get_next(char *s, int *i)
{
	int j;
	int k;
	int	quote;
	int nb_par;

	j = 0;
	quote = 0;

	while (s[j]==' ')
		j++;
	if (s[j] == '(')
	{
		nb_par = 1;
		j++;
		while (s[j] && nb_par)
		{
			if (!quote && s[j] == '(')
				nb_par++;
			if (!quote && s[j] == ')')
				nb_par--;
			if (s[j] == '\'' && quote != 2)
				quote = (quote + 1) % 2;
			else if (s[j] == '\"' && quote != 1)
				quote = (quote + 2) % 4;
			j++;
		}
		k = j;
		while (s[j]==' ')
			j++;
		//TODO libft
		if (ft_memcmp(s + j, "&&", 2) && ft_memcmp(s + j, "||", 2) && s[j])
			return (0);
		*i = j;
		char *cp = malloc(k - 1);
		memcpy(cp, s + 1, k - 2);
		cp[k - 2] = 0;
		return cp;
	}

	int cmp = 0;
	while (s[j])
	{
		if (!quote && s[j] == ')')
			return (0);
		if (!ft_memcmp(s + j, "&&", 2) || !ft_memcmp(s + j, "||", 2))
		{
			*i = j;
			cmp++;
		}

		if (cmp == 2 || !s[j + 1])
		{
			if (cmp == 2)
				*i = j;
			else
				j = *i;
			char *cp = malloc(j + 1);
			memcpy(cp, s, j);
			cp[j] = 0;
			return cp;
		}
		if (s[j] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[j] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		j++;
	}
	return (0);
}

int progress(t_cmd *cmd)
{
	if (!cmd || !cmd->txt)
		return (0);
	if (is_finish(cmd->txt))
		return 0;
	int	i = 0;
	char *ncmd = get_next(cmd->txt, &i);
	if (!ncmd)
		return (0);
	char *nncmd = strdup(cmd->txt + i + 2);

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

void do_preparse_line(t_cmd **cmd, t_data *data)
{
	if (!cmd || !*cmd)
		return;
	if ((*cmd)->soon)
		do_preparse_line(&(*cmd)->soon, data);
	else
		preparseLine(cmd, (*cmd)->txt, data);
	do_preparse_line(&(*cmd)->on_fail, data);
	do_preparse_line(&(*cmd)->on_success, data);
}



void parse_group(t_cmd **cmd, char *brut, t_data *data)
{
	if (!brut) // ctrl +d
		return;
	if (brut[0] == '\0') //ligne vide (on exit pas, on exec une commande vide)
	{
		*cmd = new_cmd();
		return;
	}
	if (cmd)
		*cmd = new_cmd_txt(brut);
	progress(*cmd);
	do_preparse_line(cmd, data);
	(void) data;
}
