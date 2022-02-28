//
// Created by plefevre on 2/11/22.
//


#include "../includes/minishell.h"

void handle_sigint(int signo) {
	if (signo == SIGINT) {
		ft_putstr_fd("\b\b  \n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void handle_sigquit(int signo) {
	if (signo == SIGQUIT) {
		rl_redisplay();
	}
}


void	getCmdSignal(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
}