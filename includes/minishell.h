//
// Created by plefevre on 1/26/22.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
#include <dirent.h>

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

int	g_exit_status;

t_list *parse_env(char **env);
t_cmd *getCmd(void);

t_list *parse_env(char **env);
int	find_rd_in(char **cmd, int *rd_in);
int	find_rd_output(char **cmd, int *rd_out);
int	is_in_str(char *str, char c);
char	*find_cmd_path(char **cmd, t_list *env);
int	is_a_file(char *str);
char	**find_cmd_argv(char **cmd, char *cmd_path);
int	check_null(char **tab, int len);
#endif
