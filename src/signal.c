/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:07:21 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 20:03:40 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	get_cmd_signal(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	exec_signal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	nothing_signal(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	cmd_signal(int sig)
{
	if (sig == 2)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	}
	else if (sig == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_status = 131;
	}
}
