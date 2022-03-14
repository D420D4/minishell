/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:42:35 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/14 19:22:04 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_cmd *new_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe = 0;
	cmd->on_success = 0;
	cmd->on_fail = 0;
	cmd->soon = 0;
	cmd->cmd = 0;
	cmd->txt = 0;
	cmd->cmd_path = 0;
	cmd->parsing_pre_analysis = 0;
	cmd->pipe = 0;
	cmd->fd_heredocs = -1;
	cmd->bonus = 0;
	return (cmd);
}

t_cmd *new_cmd_txt(char *txt)
{
	t_cmd *cmd = new_cmd();
	if (!cmd)
		return (0);
	cmd->txt = ft_strdup(txt);
	cmd->bonus = !(is_finish(txt));
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->pipe)
		free_cmd(cmd->pipe);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd)
		free_tab(cmd->cmd);
	if (cmd->txt)
		free(cmd->txt);
	if (cmd->soon)
		free_cmd(cmd->soon);
	if (cmd->parsing_pre_analysis)
		free_tab(cmd->parsing_pre_analysis);
	close_fd(cmd->fd_heredocs);
	if (cmd->on_fail)
		free_cmd(cmd->on_fail);
	if (cmd->on_success)
		free_cmd(cmd->on_success);
	free(cmd);
}

int is_in_special(char c, char *s)
{
	int i;
	int	quote;

	i = 0;
	quote = 0;

	while (s[i])
	{
		if (c == s[i] && !quote)
			return (1);
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (0);
}

//s have an even number of " and '
char **split_advanced(char *s, char *c)
{
	t_list *mots;
	char **ss;
	int i;
	int d;
	int quote;

	d = 0;
	quote = 0;
	mots = 0;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if ((!ft_memcmp(s + i, c, ft_strlen(c)) || !s[i]) && quote == 0)
		{
			char *string = ft_substr(s, d, i - d);
			if (!string)
				return (0);
			if (ft_strlen(string))
			{
				ft_lstadd_back(&mots, ft_lstnew(string));
				if (!ft_lstlast(mots)->content)
				{
					ft_lstclear(&mots, &free);
					return (0);
				}
			}
			else
			{
				free(string);
				if (!ft_memcmp(c, "|", 2))
				{
					ft_lstclear(&mots, &free);
					return (0);
				}
			}
			d = i + ft_strlen(c);
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	ss = list_to_tab(mots);
	ft_lstclear(&mots,&free);
	return (ss);
}

//Bonus, remove first spaces
char *first_word(const char *s)
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


/*
void parseLine_no_pipe(t_cmd **cmd, char **bruts, t_data *data)
{
	char	**split;
	char	*new_brut;

	if (!bruts || !*bruts)
		return;
	if (!*cmd)
		*cmd = new_cmd();
	split = split_advanced_redirections(*bruts);
	if (!split)
		return;
	new_brut = ft_strjoin_vector(len_tab(split), split, " ");
	free_tab(split);
	if (!new_brut)
		return;
	split = split_advanced(new_brut, " ");
	free(new_brut);
	if (!split)
		return;
	(*cmd)->cmd = do_redirections(split, *cmd, data);
	free_tab(split);
	parseLine_no_pipe(&((*cmd)->pipe), bruts + 1, data);
}*/

int	do_heredocs(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int	i;
	char	**split;

	split = cmd->parsing_pre_analysis;
	if (!split)
		return (1);
	i = -1;
	while(split[++i])
	{
		if (!ft_memcmp(split[i], "<<", 3))
		{
			if (!set_new_rd_in_heredoc(split[i + 1], cmd, cmd_parent, data))
				return (0);
			i++;
		}
	}
	return (1);
}

int	preparseLine_no_pipe(t_cmd **cmd, char **bruts, t_cmd *cmd_parent, t_data *data)
{
	char	**split;
	char	*new_brut;

	if (!bruts)
		return (0);
	if (!*bruts)
		return (1);
	if (is_only_space(*bruts))
		return (0);
	if (!*cmd)
		*cmd = new_cmd();
	split = split_advanced_redirections(*bruts);
	if (!split)
		return (0);
	new_brut = ft_strjoin_vector(len_tab(split), split, " ");
	free_tab(split);
	if (!new_brut)
		return (0);
	split = split_advanced(new_brut, " ");
	free(new_brut);
	if (!split)
		return (0);
	(*cmd)->parsing_pre_analysis = split;
	if (!do_heredocs(*cmd, cmd_parent, data))
		return (-1);
	return (preparseLine_no_pipe(&((*cmd)->pipe), bruts + 1, cmd_parent, data));
}

int	preparseLine(t_cmd **cmd, char *brut, t_cmd *cmd_parent, t_data *data)
{
	char 	**bruts;
	int	ret;

	bruts = split_advanced(brut, "|");
	cmd_parent->bruts = bruts; 
	ret = preparseLine_no_pipe(cmd, bruts, cmd_parent, data);
	free_tab(bruts);
	cmd_parent->bruts = NULL;
	if (ret != 1)
		return (ret);
	return (1);
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
	if (g_exit_status)
		*line = ft_strjoin("\e[1;31m➜\e[1;36m minishell: \e[1;34m", temp);
	else
		*line = ft_strjoin("\e[1;32m➜\e[1;36m minishell: \e[1;34m", temp);
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
	t_cmd *cmd;

	cmd = 0;
	if (!get_startingline(&startingline, data))
		return 0;
	brut = readline(startingline);
	free(startingline);
	if (!brut)
		return (0);
	if (!is_only_space(brut))
		add_history(brut); //on ajoute pas les lignes vides a l histo
	parse_group(&cmd, brut, data);
//	parseLine(&cmd, bruts, data);
	free(brut);
	return (cmd);
}
