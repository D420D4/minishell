/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:10:18 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/20 05:08:03 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_str(char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

int	is_a_file(char *str)
{
	DIR	*dir_ptr;
	dir_ptr = opendir(str);
	if (dir_ptr == NULL)
	{
		if (errno == ENOTDIR)
			return (1);
		return (0);
	}
	if (closedir(dir_ptr))
		perror("closedir");
	return (0);
}

int	check_null(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (tab[i] == NULL)
		{
			while (--i >= 0)
				free(tab[i]);
			free(tab);
			return (1);
		}
	}
	return (0);
}

void	close_fd(int fd)
{
	if (fd > 2)
	{
		if (close(fd))
			perror("close");
	}
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	len_cmd(t_list	*mots)
{
	int	len;

	len = 0;
	while (mots)
	{
		if (((char*) mots->content)[0] != '\0')
			len++;
		mots = mots->next;
	}
	return (len);
}


//remove "\0" element
char **list_to_tab(t_list *lst)
{
	int i;
	char **ss;

	ss = malloc(sizeof (char *) * (len_cmd(lst) + 1));
	if (!ss)
		return (0);
	i = 0;
	while (lst)
	{
		if (((char*) lst->content)[0] != '\0')
		{
			ss[i++] = ft_strdup((char*) lst->content);
			if (!ss[i-1])
			{
				free_tab(ss);
				return (0);
			}
		}
		lst = lst->next;
	}
	ss[i] = 0;
	return (ss);
}