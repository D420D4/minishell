/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:48:47 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/17 01:31:55 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (*(s + i))
		i++;
	if (fd == 2)
		write(2, "\e[1;31m", 7);
	write(fd, s, i);
	write(fd, "\n", 1);
	if (fd == 2)
		write(2, "\e[0m", 4);
}
