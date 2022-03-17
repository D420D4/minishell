/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:55:49 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/17 18:29:59 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*parse_env(char **env)
{
	t_list	*lst;

	lst = 0;
	while (*env)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	return (lst);
}

int	cmd_env(t_cmd *cmd, t_data *data)
{
	t_list	*env;

	env = data->env;
	if (cmd->cmd[1])
		ft_putstr_fd("No options or arguments needed\n", 2);
	while (env)
	{
		if (ft_strchr(env->content, '='))
		{
			ft_putstr_fd((char *) env->content, cmd->fd_out);
			ft_putstr_fd("\n", cmd->fd_out);
		}
		env = env->next;
	}
	return (0);
}

char	*getvalue(char *s, t_data *data)
{
	int		j;
	t_list	*lst;

	j = ft_strlen(s);
	if (j == 0)
		return (NULL);
	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp(s, (char *) lst->content, j)
			&& ft_strlen((char *) lst->content) >= j
			&& ((char *) lst->content)[j] == '=')
			return (lst->content + ft_strlen(s) + 1);
		else
			lst = lst->next;
	}
	return (NULL);
}

char	**env_to_tab(t_list *env)
{
	int		size;
	int		i;
	char	**tab;

	size = ft_lstsize(env);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	add_pwd(t_data *data)
{
	char	*pwd;
	t_list	*lst;
	char	*temp;

	temp = get_pwd();
	pwd = ft_strjoin("PWD=", temp);
	free(temp);
	if (!pwd)
		return ;
	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp("PWD", (char *) lst->content, 3)
			&& ft_strlen((char *) lst->content) >= 3
			&& ((char *) lst->content)[3] == '=')
		{
			free(lst->content);
			lst->content = pwd;
			return ;
		}
		else
			lst = lst->next;
	}
	ft_lstadd_back(&data->env, ft_lstnew(pwd));
}
