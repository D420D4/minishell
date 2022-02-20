/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:42:35 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/20 06:01:59 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

int	len_cmd(t_list	*mots)
{
	int	len;

	len = 0;
	while (mots)
	{
		if (((char*) mots->content)[0] != '\0')
			len++;
		mots = mots->next;
	}
	return (len);
}

//s have an even number of " and '
char **split_advanced(char *s, char *c, t_data *data)
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
	while (i <= ft_strlen(s))
	{
		if ((!memcmp(s + i, c, ft_strlen(c)) || !s[i]) && quote == 0)
		{
			char *string = ft_substr(s, d, i - d);
			if (!string)
				return (0);
			if (ft_strlen(string))
			{
				if (!memcmp(c, " ", 2))
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
			d = i + ft_strlen(c);
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	ss = malloc(sizeof (char *) * (len_cmd(mots) + 1));
	if (!ss)
	{
		ft_lstclear(&mots, &free);
		return (0);
	}
	i = 0;
	mots2 = mots;
	while (mots)
	{
		if (((char*) mots->content)[0] != '\0')
			ss[i++] = (char*) mots->content;
		mots = mots->next;
	}
	ss[i] = 0;
	ft_lstclear(&mots2,&nothing);
	return (ss);
}

//Bonus, remove first spaces
char *first_word(char *s)
{
	int	i;
	int	j;
	char *ss;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s[i] ==  ' ')
		i++;
	while (s[i + j] && s[i + j] !=  ' ')
		j++;
	ss = malloc(j + 1);
	if (!ss)
		return (0);
	j = 0;
	while (s[i + j] && s[i + j] !=  ' ')
	{
		ss[j] = s[i + j];
		j++;
	}
	ss[j] = 0;
	return (ss);
}

void parseLine(t_cmd **cmd, char **bruts, t_data *data)
{
	char	**split;
	char 	*file;

	if (!bruts || !*bruts)
		return;	
	if (!*cmd)
		*cmd = newCmd();

	split = split_advanced(*bruts, ">>", data);
	if (!split)
		return;
	file = first_word(split[1]);
	if (file)
	{
		set_new_rd_out_append(file, &((*cmd)->fd_out));
		free(file);
	}
	split = split_advanced(split[0], ">", data);
	if (!split)
		return;
	file = first_word(split[1]);
	if (file)
	{
		set_new_rd_out_trunc(file, &((*cmd)->fd_out));
		free(file);
	}
	//TODO boulot de free des split (et clarification du code)

	(*cmd)->cmd = split_advanced(split[0], " ", data);
	parseLine(&((*cmd)->pipe), bruts + 1, data);
}

int	get_startingline(char **line, t_data *data)
{
	char	*pwd;
	char	*home;
	char	*temp;

	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return (0);
	if (getcwd(pwd,4096) == NULL)
	{
		perror("getcwd");
		free(pwd);
		return (0);
	}
	home = getvalue("HOME", data);
	if (home && !ft_memcmp(pwd, home, ft_strlen(home)))
	{
		*line = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
	}
	else
		*line = pwd;
	temp = *line;
	*line = ft_strjoin("\e[1;36mminishell: ", temp);
	free(temp);
	if (*line == NULL)
		return (0);
	temp = *line;
	*line = ft_strjoin(temp, " $> \e[0m");
	free(temp);
	if (*line == NULL)
		return (0);
	return (1);

}

t_cmd *getCmd(t_data *data)
{
	char *startingline;
	char *brut;
	char **bruts;
	t_cmd *cmd;

	cmd = 0;
	if (!get_startingline(&startingline, data))
		return 0;
	brut = readline(startingline);
	add_history(brut);
	if (!brut)
		return (0);
	bruts = split_advanced(brut, "|", data);
	parseLine(&cmd, bruts, data);
	free(brut);
	free_tab(bruts);
	return (cmd);
}
