/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:49:47 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/18 00:46:24 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_a_number(char *old_content)
{
	int	i;

	i = -1;
	if (old_content[0] == '-')
		i++;
	while (old_content[++i])
	{
		if (!ft_isdigit(old_content[i]))
			return (0);
	}
	return (1);
}

static int	atoi_shlvl(char *str)
{
	int	i;
	int	n;

	if (!is_a_number(str))
		return (1);
	if (str[0] == '-')
		return (0);
	n = 0;
	i = 0;
	while (ft_isdigit(str[i]) && n < 999)
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '\0' && n < 999)
		return (n + 1);
	ft_putendl_fd("minishell : warning: shell level too high, resetting to 1", 1);
	return (1);
}

static char	*find_new_value_shlvl(char *old_content)
{
	int	value;
	char	*new_content;

	value = atoi_shlvl(old_content);
	new_content = ft_strjoin("SHLVL=", ft_itoa(value));
	return (new_content);
}

void	add_shlvl(t_data *data)
{
	t_list	*lst;
	char	*new_content;

	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp("SHLVL", (char *) lst->content, 5)
			&& ft_strlen((char *) lst->content) >= 5
			&& ((char *) lst->content)[5] == '=')
		{
			new_content = find_new_value_shlvl(lst->content + 6);
			if (new_content == NULL)
				return ;
			free(lst->content);
			lst->content = new_content;
			return ;
		}
		else
			lst = lst->next;
	}
	new_content = ft_strdup("SHLVL=1");
	if (new_content)
		ft_lstadd_back(&data->env, ft_lstnew(new_content));
}

