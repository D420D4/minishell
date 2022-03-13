/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 02:22:17 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/13 01:27:56 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_identifier(char *name, int j)
{
	if (j == 0)
	{
		if (ft_isalpha(name[j]) || name[j] == '_')
			return (1);
		return (0);
	}
	if (ft_isalpha(name[j]) || ft_isdigit(name[j]) || name[j] == '_')
		return (1);
	return (0);
}

int cmd_export(t_cmd *cmd, t_data *data)
{
	int i;
	int j;
	int added;
	int ret;
	t_list *lst;

	i = 0;
	ret = 0;
	while (cmd->cmd[++i])
	{
		added = 0;
		j = 0;
		while (cmd->cmd[i][j] && cmd->cmd[i][j] != '='
			&& is_valid_identifier(cmd->cmd[i], j))
			j++;
		if (cmd->cmd[i][j] == '=' && j != 0)
		{
			lst = data->env;
			while (lst && !added)
			{
				if (!ft_strncmp(cmd->cmd[i], (char *) lst->content, j))
				{
					free(lst->content);
					lst->content = strdup(cmd->cmd[i]);
					added = 1;
				}
				lst = lst->next;
			}
			if (!added)
				ft_lstadd_back(&(data->env), ft_lstnew(ft_strdup(cmd->cmd[i])));
		}
		else//if (cmd->cmd[i][j] && !is_valid_identifier(cmd->cmd[i], j))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->cmd[i], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			ret = 1;
		}
	}
	return (ret);
}
