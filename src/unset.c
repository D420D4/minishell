//
// Created by plefevre on 2/11/22.
//
#include "../includes/minishell.h"

void lst_del(t_list **l)
{
	t_list *t;

	t = *l;
	(*l) = t->next;
	ft_lstdelone(t, &free);
}

int cmd_unset(t_cmd *cmd, t_data *data)
{
	int i;
	int j;
	t_list **lst;

	i = 0;
	while (cmd->cmd[++i])
	{
		j = ft_strlen(cmd->cmd[i]);
		lst = &(data->env);
		while (*lst)
		{
			if (!ft_strncmp(cmd->cmd[i], (char *) (*lst)->content, j))
				lst_del(lst);
			else
				lst = &((*lst)->next);
		}
	}
	return (0);
}