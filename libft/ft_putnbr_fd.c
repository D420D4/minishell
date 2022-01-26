/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:48:47 by plefevre          #+#    #+#             */
/*   Updated: 2021/11/26 00:01:46 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
		write (fd, "0", 1);
	else if (n < 0)
	{
		write (fd, "-", 1);
		ft_putnbr_fd(-n, fd);
		return ;
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		c = '0' + n % 10;
		write(fd, &c, 1);
	}
}
