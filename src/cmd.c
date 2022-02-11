//
// Created by plefevre on 2/10/22.
//

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
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

char *remove_quote(char *s)
{
	char *ss;
	int nb_quote;
	int quote;
	int i;
	int j;

	if (!s)
		return (0);
	nb_quote = 0;
	quote = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && quote != 2 && ++nb_quote)
			quote = (quote + 1) % 2;
		if (s[i] == '\"' && quote != 1 && ++nb_quote)
			quote = (quote + 2) % 4;
	}
	ss = malloc(ft_strlen(s) - nb_quote + 1);
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
		else
			ss[++j] = s[i];
	}
	ss[++j] = 0;
	free(s);
	return (ss);
}


//s have an even number of " and '
char **split_quote(char *s, char c)
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
					ft_lstadd_back(&mots, ft_lstnew(remove_quote(string)));
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

void parseLine(t_cmd **cmd, char **bruts)
{
	if (!bruts || !*bruts)
		return;

	if (!*cmd)
		*cmd = newCmd();
	(*cmd)->cmd = split_quote(*bruts, ' ');
	parseLine(&((*cmd)->pipe), bruts + 1);
}

t_cmd *getCmd(void)
{
	char *brut;
	t_cmd *cmd;

	cmd = 0;
	brut = readline("$> ");
	add_history(brut);
	parseLine(&cmd, split_quote(brut, '|'));

	return (cmd);
}