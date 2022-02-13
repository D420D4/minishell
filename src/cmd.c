//
// Created by plefevre on 2/10/22.
//

#include "../includes/minishell.h"

t_cmd *newCmd()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe = 0;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free(cmd->cmd_path);
		free_tab(cmd->cmd_argv);
	}
}

void nothing(void *v)
{
	(void)v;
}

char *substring(char *s, char c)
{
	int i;
	char *ss;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ss = malloc(i + 1);
	if (!ss)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = 0;
	return (ss);
}

char *replace(char *s, int p, int nb, char *news)
{
	char *ss;
	int i;
	int j;
	int k;

	ss = malloc(ft_strlen(s) + ft_strlen(news) - nb + 1);
	i = 0;
	j = 0;
	k = 0;
	if (!ss)
		return (0);
	while (s[i] && i < p)
		ss[k++] = s[i++];
	while (news[j])
		ss[k++] = news[j++];
	while (s[i])
		ss[k++] = s[i++];
	ss[k] = 0;
	return (ss);
}

char *remove_quote(char *s, t_data *data)
{
	char *ss;
	char *sub;
	char *sub2;
	int quote;
	int i;
	int j;

	if (!s)
		return (0);
	quote = 0;
	i = -1;

	ss = malloc(ft_strlen(s) + 1);
	if (!ss)
		return (0);
	i = -1;
	j = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else if (s[i] == '$')
		{
			sub = substring(s + i + 1, ' ');
			sub2 = getvalue(sub, data);
			if (sub2)
				s = replace(s, i, ft_strlen(sub) + 1, sub2);
			else
				s = replace(s, i, ft_strlen(sub) + 1, "");
			i += ft_strlen(sub2) - ft_strlen(sub) - 1;
		}else
			ss[++j] = s[i];
	}
	ss[++j] = 0;
	free(s);
	s = ft_strdup(ss);
	free(ss);
	return (s);
}


//s have an even number of " and '
char **split_quote(char *s, char c, t_data *data)
{
	t_list *mots;
	t_list *mots2;
	char **ss;
	int i;
	int d;
	int quote;

	i = 0;
	d = 0;
	quote = 0;
	mots = 0;
	while (!i || s[i - 1])
	{
		if ((s[i] == c || !s[i]) && quote == 0)
		{
			char *string = ft_substr(s, d, i - d);
			if (!string)
				return (0);
			if (ft_strlen(string))
			{
				if (c == ' ')
					ft_lstadd_back(&mots, ft_lstnew(remove_quote(string, data)));
				else
					ft_lstadd_back(&mots, ft_lstnew(string));
				if (!ft_lstlast(mots)->content)
				{
					ft_lstclear(&mots, &free);
					return (0);
				}
			}
			else
				free(string);
			d = i + 1;
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}

	ss = malloc(sizeof (char *) * (ft_lstsize(mots) + 1));
	if (!ss)
	{
		ft_lstclear(&mots, &free);
		return (0);
	}
	i = 0;
	mots2 = mots;
	while (mots)
	{
		ss[i] = (char*) mots->content;
		mots = mots->next;
		i++;
	}
	ss[i] = 0;
	ft_lstclear(&mots2,&nothing);
	return (ss);
}

void parseLine(t_cmd **cmd, char **bruts, t_data *data)
{
	if (!bruts || !*bruts)
		return;

	if (!*cmd)
		*cmd = newCmd();
	(*cmd)->cmd = split_quote(*bruts, ' ',data);
	parseLine(&((*cmd)->pipe), bruts + 1, data);
}

t_cmd *getCmd(t_data *data)
{
	char *brut;
	t_cmd *cmd;

	cmd = 0;
	brut = readline(PROMPT);
	add_history(brut);
	if (!brut)
		return (0);
	parseLine(&cmd, split_quote(brut, '|', data), data);
	return (cmd);
}