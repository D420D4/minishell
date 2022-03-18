/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:49:12 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/18 01:04:40 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_export(char *var)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

void	export_null_content(t_data *data, char *var)
{
	t_list	*lst;
	char	*new_content;
	int		added;
	int		len;

	added = 0;
	len = ft_strlen(var);
	lst = data->env;
	while (lst && !added)
	{
		if (!ft_strncmp(var, (char *) lst->content, len))
			added = 1;
		else
			lst = lst->next;
	}
	if (!added)
	{
		new_content = ft_strdup(var);
		if (new_content)
			ft_lstadd_back(&(data->env), ft_lstnew(new_content));
	}
}

static	void	export_print_content(char *content, t_cmd *cmd)
{
	int	i;

	if (content[0])
	{
		ft_putstr_fd("=\"", cmd->fd_out);
		i = 0;
		while (content[++i])
		{
			if (content[i] == '"')
				ft_putstr_fd("\\\"", cmd->fd_out);
			else
				ft_putchar_fd(content[i], cmd->fd_out);
		}
		ft_putchar_fd('\"', cmd->fd_out);
	}
	ft_putchar_fd('\n', cmd->fd_out);
}

void	print_env_export(t_cmd *cmd, t_data *data)
{
	int		j;
	int		i;
	char	*content;
	char	**split;

	split = list_to_tab(data->env);
	ft_sort_tab(split, len_tab(split), ft_strcmp_export);
	if (split == NULL)
		return ;
	j = -1;
	while (split[++j])
	{	
		content = split[j];
		ft_putstr_fd("declare -x ", cmd->fd_out);
		i = -1;
		while (content[++i] != '=' && content[i])
			ft_putchar_fd(content[i], cmd->fd_out);
		export_print_content(content + i, cmd);
	}
	free_tab(split);
}

char	*ft_strjoin_added(char *content, char *var)
{
	int		i;
	char	*new_content;
	char	*temp;

	i = 0;
	while (content[i] != '=' && content[i])
		i++;
	if (content[i] == '=')
		return (ft_strjoin(content, var));
	temp = ft_strjoin(content, "=");
	new_content = ft_strjoin(temp, var);
	free(temp);
	return (new_content);
}
