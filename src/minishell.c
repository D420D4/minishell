//
// Created by plefevre on 1/26/22.
//
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "debug.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>

t_cmd *newCmd()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe = 0;
	return (cmd);
}

void parseLine(t_cmd **cmd, char **bruts)
{
	if (!bruts || !*bruts)
		return;

	if (!*cmd)
		*cmd = newCmd();
	(*cmd)->cmd = ft_split(*bruts, ' ');
	parseLine(&((*cmd)->pipe), bruts + 1);
}

t_cmd *getCmd(void)
{
	char *brut;
	t_cmd *cmd;

	cmd = 0;
	brut = readline("$> ");
	parseLine(&cmd, ft_split(brut, '|'));

	return (cmd);
}

int main(int ac, char **av, char **envp)
{
	t_data data;
	t_cmd *cmd;

	(void) ac;
	(void) av;
	(void) envp;
	(void) data;
	data.env = parse_env(envp);
	cmd = 0;

	while (!cmd || ft_memcmp(cmd->cmd[0], "exit", 5))
	{
		cmd = getCmd();
		print_cmd(cmd);

	}
	return (0);
}

