NAME	= minishell
SRC		= minishell.c\
		  builtin_functions.c\
		  bonus_and_or.c\
		  cd.c\
		  header.c\
		  cmd.c\
		  cmd_analyse.c\
		  debug.c\
		  echo.c\
		  env.c\
		  execute.c\
		  execute2.c\
		  exit.c\
		  export.c\
		  find_cmd_argv.c\
		  find_cmd_path.c\
		  ft_strjoin_vector.c\
		  get_next_line/get_next_line.c\
		  get_next_line/get_next_line_utils.c\
		  pwd.c\
		  redirection_in.c\
		  redirection_out.c\
		  signal.c\
		  split_redirection.c\
		  unset.c\
		  utils.c\
		  utils_str.c\
		  utils_tabs.c\
		  wildcards.c\
		  wildcards2.c\

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
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Linking "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"
	@$(CC) -o $(NAME) $(addprefix $(OBJDIR),$(OBJ)) libft/libft.a $(LFLAGS)

bonus: $(OBJSBONUS) libft/libft.a
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Linking "
	@tput sgr0
	@tput setaf 6
	@$(CC) -o $(NAME) $(OBJSBONUS) $(LFLAGS) libft/libft.a --no-print-directory

$(OBJDIR)%.o: $(SRCDIR)%.c
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Compiling "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/get_next_line
	@$(CC) $(LFLAGS) $(CFLAGS) -c -I $(LIBDIR) -o $@ $<

clean:
	@/bin/rm -f $(addprefix $(OBJDIR),$(OBJ))
	@/bin/rm -f $(addprefix $(OBJDIR),$(OBJBONUS))
	@/bin/rm -rf $(OBJDIR)
	@make clean -C ./libft --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "clean done"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "fclean done"


libft/libft.a:
	@make bonus -C ./libft --no-print-directory

print_name:
	@tput bold
	@tput setaf 208
	@printf "%-10s " $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus print_name
