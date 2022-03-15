/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:30:08 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 16:40:21 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_negative(char *cmd, int *i)
{
	int	negative;
	int	j;

	j = 0;
	while ((cmd[j] >= 9 && cmd[j] <= 13) || cmd[j] == ' ')
		j++;
	negative = 0;
	if (cmd[j] == '+' || cmd[j] == '-')
	{
		if (cmd[j] == '-')
		{
			j++;
			negative = 1;
		}
	}
	*i = j;
	return (negative);
}

static int	exit_code(char *cmd)
{
	unsigned long	code;
	int				i;
	int				negative;
	unsigned long	limit;

	limit = (unsigned long) LONG_MAX + 1;
	negative = is_negative(cmd, &i);
	code = 0;
	while (cmd[i] >= '0' && cmd[i] <= '9' && code < limit)
	{
		code = 10 * code + cmd[i] - '0';
		i++;
	}
	if (cmd[i] != '\0' || (negative == 0 && code >= limit)
		|| (negative == 1 && code > limit))
		return (-1);
	code %= 256;
	if (negative)
		code = (256 + (-1) * code) % 256;
	return ((int) code);
}

int	cmd_exit(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int	ret;

	if ((cmd == 0 && cmd_parent == 0) || (cmd == cmd_parent && !cmd->pipe))
		ft_putstr_fd("exit\n", 1);
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
			ft_putendl_fd("minishell: exit : too many arguments", 2);
			return (1);
		}
	}
	exit_clean(data, cmd_parent);
	exit(ret);
}

//A utiliser uniuement avant de sortir du programme ou d un fork !
void	exit_clean(t_data *data, t_cmd *cmd_parent)
{
	ft_lstclear(&(data->env), &free);
	free_cmd(cmd_parent);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
}
