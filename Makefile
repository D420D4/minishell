NAME	= minishell
SRC		= minishell.c\
			debug.c\
			env.c


SRCBONUS= bonus.c

OBJ		= $(patsubst %.c, %.o, $(SRC))
OBJBONUS= $(patsubst %.c, %.o, $(SRCBONUS))

OBJS		= $(addprefix ${OBJDIR}, ${OBJ})
OBJSBONUS	= $(addprefix ${OBJDIR},${OBJBONUS})

SRCDIR	= src/
OBJDIR	= obj/
LIBDIR	= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -lreadline

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(LFLAGS) -o $(NAME) $(addprefix $(OBJDIR),$(OBJ)) libft/libft.a

bonus: $(OBJSBONUS) libft/libft.a
	$(CC) $(LFLAGS) -o $(NAME) $(OBJSBONUS) $(LFLAGS) libft/libft.a

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -I $(LIBDIR) -o $@ $<

clean:
	/bin/rm -f $(addprefix $(OBJDIR),$(OBJ))
	/bin/rm -f $(addprefix $(OBJDIR),$(OBJBONUS))
	/bin/rm -rf $(OBJDIR)
	make clean -C ./libft

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./checker
	make fclean -C ./libft

libft/libft.a:
	make bonus -C ./libft

re: fclean all

.PHONY: all clean fclean re bonus