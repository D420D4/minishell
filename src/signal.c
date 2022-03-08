//
// Created by plefevre on 2/11/22.
//


#include "../includes/minishell.h"

void handle_sigint(int signo) {
	if (signo == SIGINT) {
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
		exit(1);
	}
}

void	getCmdSignal(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	execSignal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}

void	nothingSignal(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}
