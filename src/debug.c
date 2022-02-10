//
// Created by plefevre on 2/9/22.
//

#include <stdio.h>
#include "../includes/minishell.h"

void print_env(t_data *data)
{
	t_list *env = data->env;

	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}
void print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	if(!cmd)
	{
		printf("ERROR cmd\n");
		return;
	}

	printf ("%d << >> %d : ", cmd->fd_in, cmd->fd_out);
	while (cmd->cmd[i])
	{
		printf("[%s] ", cmd->cmd[i]);
		i++;
	}
	printf("\n");
	if (cmd->pipe)
	{
		printf("| ");
		print_cmd(cmd->pipe);
	}
}
