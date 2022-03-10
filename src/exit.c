/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:30:08 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/10 12:54:45 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exit_code(char *cmd)
{
	unsigned long	code;
	int	i;
	int	negative;
	unsigned long	limit;

	limit = (unsigned long) LONG_MAX + 1;
	i = -1;
	negative = 0;
	if (cmd[0] == '-')
	{
		negative = 1;
		i++;
	}
	code = 0;
	while (cmd[++i] >= '0' && cmd[i] <= '9' && code < limit)
		code = 10 * code + cmd[i] - '0';
	if (cmd[i] != '\0' || (negative == 0 && code >= limit)
		|| (negative == 1 && code > limit))
		return (-1);
	code %= 256;
	if (negative)
		code =  (256 + (-1) * code) % 256;
	return ((int) code);
}

int	cmd_exit(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int	ret;

	if (cmd_parent)
		ft_putstr_fd("exit\n", cmd->fd_out);
	if (!cmd || cmd->cmd[1] == NULL)
		ret = 0;
	else
	{
		ret = exit_code(cmd->cmd[1]);
		if (ret == -1)
		{
			ft_putstr_fd("minishell: exit : ", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			ret = 2;
		}
		else if (cmd->cmd[2] != NULL)
		{
			ft_putstr_fd("minishell: exit : ", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			ft_putendl_fd(": too many arguments", 2);
			return (1);
		}
	}
	ft_lstclear(&(data->env), &free);
	free_cmd(cmd_parent);
	exit_clean();
	exit(ret);
}


void exit_clean(void)
{
	rl_clear_history();
}