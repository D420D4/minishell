/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:32:53 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/07 00:23:08 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024
# include <unistd.h>
# include <stdlib.h>

typedef struct s_listbuf
{
	int					fd;
	int					p;
	int					res;
	char				buff[BUFFER_SIZE];
	struct s_listbuf	*next;
}						t_list_buf;

char		*get_next_line(int fd);
char		*prolonge_malloc(char *s, int size);
t_list_buf	*lst_new(int fd);
t_list_buf	*lst_search(t_list_buf **list, int fd);
void		lst_remove(t_list_buf **list, int fd);

#endif
