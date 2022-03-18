/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:15:39 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/18 01:04:37 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
	char			**cmd;
	char			*txt;
	char			**bruts;
	struct s_cmd	*pipe;
	struct s_cmd	*soon;
	struct s_cmd	*on_success;
	struct s_cmd	*on_fail;
	int				fd_out;
	int				fd_in;
	int				fd_heredocs;
	char			*cmd_path;
	int				pid;
	char			**parsing_pre_analysis;
	int				bonus;
}	t_cmd;

extern int	g_exit_status;

//HEADER
void	print_header(void);

//CREATE ENV
t_list	*parse_env(char **env);
void	add_pwd(t_data *data);
void	add_shlvl(t_data *data);

//CMD
t_cmd	*get_cmd(t_data *data);
t_cmd	*new_cmd(void);
t_cmd	*new_cmd_txt(char *txt);
void	free_cmd(t_cmd *cmd);

// PARSING
int		check_parenthesis(char *s);
int		check_syntax(char *brut);
int		preparse_line(t_cmd **cmd, char *brut, t_cmd *cmd_parent, t_data *data);
int		is_finish(char *txt);
int		is_in_special(char c, char *s);
char	**split_advanced_redirections(char *s);
char	**split_advanced(char *s, char *c);
void	parse_group(t_cmd **cmd, char *brut, t_data *data);

//ANALYSE

int		set_new_rd_in_open(char *filename_brut, t_cmd *cmd, t_data *data);
int		set_new_rd_in_heredoc(char *limiter_brut, t_cmd *cmd,
			t_cmd *cmd_parent, t_data *data);
int		set_new_rd_out_trunc(char *filename_brut, int *rd_out, t_data *data);
int		set_new_rd_out_append(char *filename_brut, int *rd_out, t_data *data);
int		inner_quote_1(char **s, int *i, t_data *data);
int		inner_quote_2(char **s, int *i);
int		progress(t_cmd *cmd);
char	*transform(char *original, t_data *data);
char	**do_redirections(t_cmd *cmd, t_data *data);
char	*find_filename(char *filename_brut, t_data *data);
void	do_var(char **s, int *f, t_data *data);

// EXEC
int		exec_cmds(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int		exec_cmd(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int		wait_cmd(t_cmd *cmd, t_cmd *cmd_parent);
char	*find_cmd_path(char **cmd, t_list *env);
void	analyse_line(t_cmd *cmd, t_data *data);

// BUILTIN
int		execute_builtin(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int		is_in_builtin(char *cmd_name);
int		cmd_echo(t_cmd *cmd);
int		cmd_env(t_cmd *cmd, t_data *data);
int		cmd_export(t_cmd *cmd, t_data *data);
int		cmd_unset(t_cmd *cmd, t_data *data);
int		cmd_cd(char **cmd, t_data *data);
int		cmd_pwd(t_cmd *cmd);
int		cmd_exit(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
char	*ft_strjoin_added(char *content, char *var);
void	export_null_content(t_data *data, char *var);
void	print_error_export(char *var);
void	print_env_export(t_cmd *cmd, t_data *data);

//SIGNAL
void	exec_signal(void);
void	nothing_signal(void);
void	get_cmd_signal(void);
void	cmd_signal(int sig);
void	quit_heredoc(int sig);
void	save_before_signal(int mode, int fd, char *limiter);

//WILDCARDS
int		check_sequence(char *sequence, char **d_name);
int		check_first_wildards(char **s, char **d_name, t_data *data);
int		check_end_sequence(char *sequence, char *d_name);
char	**do_wildcards_word(char *s, t_data *data);

//EXIT
void	exit_clean(t_data *data, t_cmd *cmd_parent);

//UTILS
int		is_in(char c, char *s);
int		len_cmd(t_list *mots);
int		is_a_file(char *str);
char	*get_pwd(void);
char	**env_to_tab(t_list *env);
char	*getvalue(char *s, t_data *data);
void	close_fd(int fd);

//UTILS TABS
int		len_tab(char **tab);
char	**list_to_tab(t_list *lst);
char	*ft_strjoin_vector(int size, char **strs, char *sep);
void	ft_sort_tab(char **tab, int size, int (f)(char *, char *));
void	free_tab(char **tab);

//UTILS STR
int		is_in_str(char *str, char c);
int		ft_strcmp_wildcards(char *s1, char *s2);
int		ft_strcmp_export(char *s1, char *s2);
int		is_only_space(char *string);
char	*ft_strdup_no_quote(char *limiter_brut);

#endif
