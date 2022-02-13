NAME	= minishell
SRC		= minishell.c\
			debug.c\
			env.c\
			cmd.c\
			execute.c\
			find_cmd_argv.c\
			find_cmd_path.c\
			redirection_in.c\
			redirection_out.c\
			utils.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
			signal.c\
			echo.c\
			builtin_functions.c\
			export.c\
			unset.c\

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

$(NAME): libft/libft.a $(OBJS)
	$(CC) -o $(NAME) $(addprefix $(OBJDIR),$(OBJ)) libft/libft.a $(LFLAGS)

bonus: $(OBJSBONUS) libft/libft.a
	$(CC) -o $(NAME) $(OBJSBONUS) $(LFLAGS) libft/libft.a

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/get_next_line
	$(CC) $(LFLAGS) $(CFLAGS) -c -I $(LIBDIR) -o $@ $<

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