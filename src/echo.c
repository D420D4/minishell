//
// Created by plefevre on 2/11/22.
//
#include "../includes/minishell.h"

int	cmd_echo(char **av)
{
	int n;
	int i;

	n = !ft_memcmp(av[1], "-n", 3);
	av += 1 + n;
	i = 0;
	while (av[i])
	{
		printf("%s", av[i++]);
		if (av[i])
			printf(" ");
	}
	if (!n)
		printf("\n");
	return (0);
}