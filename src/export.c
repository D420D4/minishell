/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 02:22:17 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/14 02:29:06 by lcalvie          ###   ########.fr       */
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

char	*ft_strdup_without_plus(const char *s)
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

void	print_env_export(t_cmd *cmd, t_data *data)
{
	t_list *env;
	int	i;
	char	*content;
	
	env = data->env;
	while (env)
	{
		content = (char *) env->content;
		ft_putstr_fd("declare -x ", cmd->fd_out);
		i = -1;
		while (content[++i] != '=')
			ft_putchar_fd(content[i], cmd->fd_out);
		ft_putstr_fd("=\"", cmd->fd_out);
		while(content[++i])
		{
			if (content[i] == '"')
				ft_putstr_fd("\\\"", cmd->fd_out);
			else
				ft_putchar_fd(content[i], cmd->fd_out);
		}
		ft_putstr_fd("\"\n", cmd->fd_out);
		env = env->next;
	}
}

int	cmd_export(t_cmd *cmd, t_data *data)
{
	int i;
	int j;
	int added;
	int ret;
	t_list *lst;
	char	*new_content;

	i = 0;
	ret = 0;
	while (cmd->cmd[++i])
	{
		added = 0;
		j = 0;
		while (cmd->cmd[i][j] && cmd->cmd[i][j] != '=' && ft_memcmp(cmd->cmd[i] + j,"+=", 2)
			&& is_valid_identifier(cmd->cmd[i], j))
			j++;
		if ((cmd->cmd[i][j] == '='  || !ft_memcmp(cmd->cmd[i] + j,"+=", 2)) && j != 0)
		{
			lst = data->env;
			while (lst && !added)
			{
				if (!ft_strncmp(cmd->cmd[i], (char *) lst->content, j))
					added = 1;
				else
					lst = lst->next;
			}
			if (added)
			{
				if (cmd->cmd[i][j] == '=')
					new_content = ft_strdup(cmd->cmd[i]);
				else
					new_content = ft_strjoin(lst->content, cmd->cmd[i] + j + 2);
				if (new_content)
				{
					free(lst->content);
					lst->content = new_content;
				}
			}
			else
			{
				if (cmd->cmd[i][j] == '=')
					new_content = ft_strdup(cmd->cmd[i]);
				else
					new_content = ft_strdup_without_plus(cmd->cmd[i]);
				if (new_content)
					ft_lstadd_back(&(data->env), ft_lstnew(new_content));
			}
		}
		else if (cmd->cmd[i][j] || j == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->cmd[i], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			ret = 1;
		}
	}
	if (cmd->cmd[1] == NULL)
		print_env_export(cmd, data);
	return (ret);
}
