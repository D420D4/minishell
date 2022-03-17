/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:46:15 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/16 15:46:19 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_finish(char *txt)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (txt[i] == ' ')
		i++;
	if (txt[i] == '(')
		return (0);
	while (txt[i])
	{
		if (!quote && txt[i] == '&' && txt[i + 1] == '&')
			return (0);
		if (!quote && txt[i] == '|' && txt[i + 1] == '|')
			return (0);
		if (txt[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (txt[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

static int	do_preparse_line(t_cmd **cmd, t_cmd **cmd_parent, t_data *data)
{
	int	ret;

	if (!cmd || !*cmd)
		return (1);
	if ((*cmd)->soon)
		ret = do_preparse_line(&(*cmd)->soon, cmd_parent, data);
	else
		ret = preparse_line(cmd, (*cmd)->txt, *cmd_parent, data);
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

static void	do_error_cmd(t_cmd **cmd)
{
	if (*cmd)
		free_cmd(*cmd);
	ft_putstr_fd("syntax error\n", 2);
	g_exit_status = 2;
	*cmd = new_cmd();
}

void	parse_group(t_cmd **cmd, char *brut, t_data *data)
{
	int	ret;

	if (!brut)
		return ;
	if (is_only_space(brut))
		*cmd = new_cmd();
	else if (!check_syntax(brut) || !check_parenthesis(brut))
		do_error_cmd(cmd);
	else
	{
		*cmd = new_cmd_txt(brut);
		progress(*cmd);
		ret = do_preparse_line(cmd, cmd, data);
		if (ret == 0)
			do_error_cmd(cmd);
		else if (ret == -1)
		{
			free_cmd(*cmd);
			*cmd = new_cmd();
		}
	}
}
