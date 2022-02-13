//
// Created by plefevre on 1/26/22.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "\e[1;36m$> \e[0m"
# include "../libft/libft.h"
# include "../includes/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

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
	char	*cmd_path;
	char	**cmd_argv;
	int	pid;
}	t_cmd;

extern int g_exit_status;

t_list *parse_env(char **env);
t_cmd *getCmd(t_data *data);

t_list *parse_env(char **env);
int	find_rd_in(char **cmd, int *rd_in);
int	find_rd_output(char **cmd, int *rd_out);
int	is_in_str(char *str, char c);
char	*find_cmd_path(char **cmd, t_list *env);
int	is_a_file(char *str);
char	**find_cmd_argv(char **cmd, char *cmd_path);
int	check_null(char **tab, int len);
int	exec_cmd(t_cmd *cmd, t_data data);
void	getCmdSignal(void);
char *getvalue(char *s, t_data *data);

int	execute_builtin(t_cmd *cmd, t_data *data);
int cmd_echo(char **cmd);
int cmd_env(t_cmd *cmd, t_data *data);
int cmd_export(t_cmd *cmd, t_data *data);
int cmd_unset(t_cmd *cmd, t_data *data);
void	close_fd(int fd);
void	free_tab(char **tab);
char	**env_to_tab(t_list *env);

#endif
