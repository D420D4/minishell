//
// Created by plefevre on 2/11/22.
//
#include "../includes/minishell.h"

int cmd_export(t_cmd *cmd, t_data *data)
{
	int i;
	int j;
	int added;
	t_list *lst;

	i = 0;
	while (cmd->cmd[++i])
	{
		added = 0;
		j = 0;
		while (cmd->cmd[i][j] && cmd->cmd[i][j] != '=')
			j++;
		if (cmd->cmd[i][j])
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
	}
	return (0);
}