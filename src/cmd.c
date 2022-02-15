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
	cmd->cmd = 0;
	cmd->cmd_path = 0;
	cmd->cmd_argv = 0;
	cmd->pipe = 0;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;

	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_argv)
		free_tab(cmd->cmd_argv);
	if (cmd->cmd)
		free_tab(cmd->cmd);
	free(cmd);
}

void nothing(void *v)
{
	(void)v;
}




char	*replace(char *s, char *word, char *new_word)
{
	char *ss;
	int i;
	int j;
	int p;

	if (!ft_strnstr(s, word, ft_strlen(s)))
		return (strdup(s));
	ss = malloc(ft_strlen(s) + 1 - ft_strlen(word) + ft_strlen(new_word));
	if (!ss)
	{
		free(s);
		return (0);
	}
	i = 0;
	j = 0;
	while (s[i] && word[j])
	{
		if (s[i] != word[j])
			j = -1;
		ss[i] = s[i];
		j++;
		i++;
	}
	p = i;
	if (!word[j])
	{
		i-= ft_strlen(word);
		j = 0;
		while (new_word[j])
			ss[i++] = new_word[j++];

	}
	while (s[p])
		ss[i++] = s[p++];
	ss[i] = 0;
	free(s);
	return (ss);
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
					ft_lstadd_back(&mots, ft_lstnew(transform(string, data)));
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
	char **bruts;
	t_cmd *cmd;

	cmd = 0;
	brut = readline(PROMPT);
	add_history(brut);
	if (!brut)
		return (0);
	bruts = split_quote(brut, '|', data);
	parseLine(&cmd, bruts, data);
	free(brut);
	free_tab(bruts);
	return (cmd);
}