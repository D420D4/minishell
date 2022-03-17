/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 03:21:54 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 15:30:28 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_identifier_unset(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if ((i == 0 && !ft_isalpha(name[i]) && name[i] != '_')
			|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(name, 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			return (0);
		}
	}
	return (1);
}

static void	lst_del(t_list **l)
{
	t_list	*t;

	t = *l;
	(*l) = t->next;
	ft_lstdelone(t, &free);
}

int	cmd_unset(t_cmd *cmd, t_data *data)
{
	int		i;
	int		ret;
	t_list	**lst;

	i = 0;
	ret = 0;
	while (cmd->cmd[++i])
	{
		if (!is_valid_identifier_unset(cmd->cmd[i]))
			ret = 1;
		else
		{
			lst = &(data->env);
			while (*lst)
			{
				if (!ft_strncmp(cmd->cmd[i], (char *)(*lst)->content,
					ft_strlen(cmd->cmd[i])))
					lst_del(lst);
				else
					lst = &((*lst)->next);
			}
		}
	}
	return (ret);
}
