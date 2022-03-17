/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 02:22:17 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 17:57:00 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_identifier_export(char *name, int j)
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

static char	*ft_strdup_without_plus(const char *s)
{
	int		i;
	int		plus;
	char	*ss;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	ss = (char *)malloc(sizeof(char) * i);
	if (!ss)
		return (0);
	plus = 0;
	i = 0;
	while (s[i])
	{
		if (!plus && s[i] == '+')
			plus = 1;
		else
			ss[i - plus] = s[i];
		i++;
	}
	ss[i - plus] = s[i];
	return (ss);
}

static void	export_new_content(t_data *data, char *var, int j, int added)
{
	t_list	*lst;
	char	*new_content;

	lst = data->env;
	while (lst && !added)
	{
		if (!ft_strncmp(var, (char *) lst->content, j))
			added = 1;
		else
			lst = lst->next;
	}
	if (var[j] == '=')
		new_content = ft_strdup(var);
	else if (added)
		new_content = ft_strjoin(lst->content, var + j + 2);
	else
		new_content = ft_strdup_without_plus(var);
	if (added && new_content)
	{
		free(lst->content);
		lst->content = new_content;
	}
	else if (new_content)
		ft_lstadd_back(&(data->env), ft_lstnew(new_content));
}

int	cmd_export(t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	ret = 0;
	while (cmd->cmd[++i])
	{
		j = 0;
		while (cmd->cmd[i][j] && is_valid_identifier_export(cmd->cmd[i], j))
			j++;
		if ((cmd->cmd[i][j] == '=' || !ft_memcmp(cmd->cmd[i] + j, "+=", 2))
			&& j != 0)
			export_new_content(data, cmd->cmd[i], j, 0);
		else if (cmd->cmd[i][j] || j == 0)
		{
			print_error_export(cmd->cmd[i]);
			ret = 1;
		}
		else if (!(cmd->cmd[i][j]))
			export_null_content(data, cmd->cmd[i]);
	}
	if (cmd->cmd[1] == NULL)
		print_env_export(cmd, data);
	return (ret);
}
