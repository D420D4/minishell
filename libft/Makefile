# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plefevre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 11:23:15 by plefevre          #+#    #+#              #
#    Updated: 2021/12/05 19:04:51 by plefevre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
SRC     		= ft_atoi.c \
				  ft_bzero.c \
				  ft_calloc.c  \
				  ft_isalnum.c \
				  ft_isalpha.c \
				  ft_isascii.c \
				  ft_isdigit.c \
				  ft_isprint.c \
				  ft_memchr.c \
				  ft_memcmp.c \
				  ft_memcpy.c \
				  ft_memmove.c \
				  ft_memset.c \
				  ft_strchr.c \
				  ft_strdup.c \
				  ft_strlcat.c \
				  ft_strlcpy.c \
				  ft_strlen.c \
				  ft_strncmp.c \
				  ft_strnstr.c \
				  ft_strrchr.c \
				  ft_tolower.c \
				  ft_toupper.c \
				  ft_substr.c \
				  ft_strjoin.c \
				  ft_strtrim.c \
				  ft_split.c \
				  ft_itoa.c \
				  ft_strmapi.c \
				  ft_striteri.c \
				  ft_putchar_fd.c \
				  ft_putstr_fd.c \
				  ft_putendl_fd.c \
				  ft_putnbr_fd.c
SRC_BONUS		= ft_lstnew.c \
				  ft_lstadd_front.c \
				  ft_lstsize.c \
				  ft_lstlast.c \
				  ft_lstadd_back.c \
				  ft_lstdelone.c \
				  ft_lstclear.c \
				  ft_lstiter.c \
				  ft_lstmap.c 
OBJ				= $(patsubst %.c, %.o, $(SRC))
OBJ_BONUS		= $(patsubst %.c, %.o, $(SRC_BONUS))
LIBDIR	= ./

all: $(NAME)

$(NAME): $(OBJ)
	ar rc libft.a $(OBJ)
bonus: $(OBJ) $(OBJ_BONUS)
	ar rc libft.a $(OBJ) $(OBJ_BONUS)

%.o: %.c
	gcc -c -Wextra -Wall -Werror -I $(LIBDIR) -o $@ $< 

clean:
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re:	fclean all
