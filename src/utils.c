/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:10:18 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/14 18:00:22 by lcalvie          ###   ########.fr       */
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
		if (((char*) mots->content) != NULL)
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
		if (((char*) lst->content) != NULL)
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

int	ft_strcmp(char *s1, char *s2)
{
	char	c1;
	char	c2;
	
	c1 = 0;
	c2 = 0;
	while (c1 == c2 && *s1 && *s2)
	{
		c1 = s1[0];
		c2 = s2[0];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		s1++;
		s2++;
	}
	if (c1 == c2)
		return (s1[0] - s2[0]);
	return (c1 - c2);
}

void	ft_sort_vector(char **vector, int size)
{
	int		i;
	int		j;
	char	*str_temp;

	if (size <= 1)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(vector[i], vector[j]) < 0)
			{
				str_temp = &(vector[i][0]);
				vector[i] = &(vector[j][0]);
				vector[j] = str_temp;
			}
			j++;
		}
		i++;
	}
}

int	len_tab(char **tab)
{
	int	size;

	if (!tab)
		return (0);
	size = 0;
	while (tab[size])
		size++;
	return (size);
}

int	is_only_space(char *string)
{
	int i;

	i = -1;
	while (string[++i])
	{
		if (string[i] != ' ')
			return (0);
	}
	return (1);
}
