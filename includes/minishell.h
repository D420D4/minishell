//
// Created by plefevre on 1/26/22.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

typedef struct s_data
{
	t_list		*env;
}	t_data;

typedef struct s_cmd
{
	char	**cmd;
	struct s_cmd *pipe;
	int fd_out;
	int fd_in;
}	t_cmd;

t_list *parse_env(char **env);

#endif
