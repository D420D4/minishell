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
	*i = j;
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
		if (ft_memcmp(s + j, "&&", 2) && ft_memcmp(s + j, "||", 2) && s[j])
			return (0);
		char *cp = malloc(k - 1 - *i);
		memcpy(cp, s + 1 + *i, k - 2 - *i);
		cp[k - 2 - *i] = 0;
		*i = j;
		return cp;
	}

	int cmp = 0;
	while (s[j])
	{
		if (!ft_memcmp(s + j, "&&", 2) || !ft_memcmp(s + j, "||", 2))
		{
			*i = j;
			cmp++;
		}
		if (cmp == 2 || !s[j + 1])
		{
//			if (cmp == 2)
//				*i = j;
//			else
				j = *i;
			char *cp = malloc(j + 1);
			memcpy(cp, s, j);
			cp[j] = 0;
			return (cp);
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

int	do_preparse_line(t_cmd **cmd, t_cmd **cmd_parent,t_data *data)
{
	int ret;

	if (!cmd || !*cmd)
		return (1);
	if ((*cmd)->soon)
		ret = do_preparse_line(&(*cmd)->soon, cmd_parent, data);
	else
		ret = preparseLine(cmd, (*cmd)->txt, *cmd_parent, data);
	if (ret != 1)
		return (ret);
	ret = do_preparse_line(&(*cmd)->on_fail, cmd_parent, data);
	if (ret != 1)
		return (ret);
	ret = do_preparse_line(&(*cmd)->on_success, cmd_parent, data);
	if (ret != 1)
		return (ret);
	return (1);
}

int check_parenthesis_left(char *s, int i)
{
	if (i == 0)
		return (0);
	if (s[i - 1] == ' ' || s[i - 1] == '(')
		return (check_parenthesis_left(s, i - 1));
	if (i > 1 && ((s[i - 1] == '&' && s[i - 2] == '&') ||(s[i - 1] == '|' && s[i - 2] == '|')))
		return (0);
	return (1);
}

int check_parenthesis_right(char *s, int i)
{
	if (i == ft_strlen(s) - 1)
		return (0);
	if (s[i + 1] == ' ' || s[i + 1] == ')')
		return (check_parenthesis_right(s, i + 1));
	if (i < ft_strlen(s) - 1 && ((s[i + 1] == '&' && s[i + 2] == '&') ||(s[i + 1] == '|' && s[i + 2] == '|')))
		return (0);
	return (1);
}

//Check if () are ok with && and ||
int check_parenthesis(char *s)
{
	int i;
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

void parse_group(t_cmd **cmd, char *brut, t_data *data)
{
	int	ret;

	if (!brut) // ctrl +d
		return;
	if (is_only_space(brut)) //ligne vide (on exit pas, on exec une commande vide)
		*cmd = new_cmd();
	else if (!check_syntax(brut) || !check_parenthesis(brut))
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status = 2;
		*cmd = new_cmd();
	}
	else
	{
		*cmd = new_cmd_txt(brut);
		progress(*cmd);
		ret = do_preparse_line(cmd, cmd, data);
		if (ret == 0)
		{
			ft_putstr_fd("syntax error\n", 2);
			g_exit_status = 2;
			free_cmd(*cmd);
			*cmd = new_cmd();
		}
		else if (ret == -1)
		{
			free_cmd(*cmd);
			*cmd = new_cmd();
		}
	}
}
