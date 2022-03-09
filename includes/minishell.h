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
# include <limits.h>
# include <sys/wait.h>

typedef struct s_data
{
	t_list		*env;
}	t_data;

typedef struct s_cmd
{
	char	**cmd;
	char	*txt;
	struct s_cmd *pipe;
	struct s_cmd *soon;
	struct s_cmd *on_success;
	struct s_cmd *on_fail;
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
int	exec_cmd(t_cmd *cmd, t_data *data);
int	exec_cmds(t_cmd *cmd, t_data *data);
void	getCmdSignal(void);
char *getvalue(char *s, t_data *data);
void do_wildcards(char **s, int *i);
char	**split_advanced_redirections(char *s);

int execute_builtin(t_cmd *cmd, t_data *data);
int is_in_builtin(char *cmd_name);
int cmd_echo(t_cmd *cmd);
int cmd_env(t_cmd *cmd, t_data *data);
int cmd_export(t_cmd *cmd, t_data *data);
int cmd_unset(t_cmd *cmd, t_data *data);
int cmd_cd(char **cmd, t_data *data);
int cmd_pwd(t_cmd *cmd);
int cmd_exit(t_cmd *cmd, t_data *data);
void	close_fd(int fd);
void	free_tab(char **tab);
char	**env_to_tab(t_list *env);
void	free_cmd(t_cmd *cmd);
char	*transform(char *original, t_data *data);
void exit_clean(void);
char **list_to_tab(t_list *lst);
void	ft_sort_vector(char **vector, int size);
char	*ft_strjoin_vector(int size, char **strs, char *sep);
void	execSignal(void);
void	nothingSignal(void);
int	len_tab(char **tab);
void	set_new_rd_in_open(char *filename, int *rd_in);
int	set_new_rd_in_heredoc(char *limiter, int *rd_in);
void	set_new_rd_out_trunc(char *filename, int *rd_out);
void	set_new_rd_out_append(char *filename, int *rd_out);
char	**do_redirections(char **split, t_cmd *cmd);
void 	print_header(void);
t_cmd	*new_cmd(void);
char **split_advanced(char *s, char *c, t_data *data);
void parseLine(t_cmd **cmd, char *brut, t_data *data);
void parse_group(t_cmd **cmd, char *brut, t_data *data);
t_cmd *new_cmd_txt(char *txt);

#endif
