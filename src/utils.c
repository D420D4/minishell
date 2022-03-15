/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:10:18 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 18:47:28 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	close_fd(int fd)
{
	if (fd > 2)
	{
		if (close(fd))
			perror("close");
	}
}

int	len_cmd(t_list *mots)
{
	int	len;

	len = 0;
	while (mots)
	{
		if (((char *) mots->content) != NULL)
			len++;
		mots = mots->next;
	}
	return (len);
}
