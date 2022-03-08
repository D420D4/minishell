//
// Created by plefevre on 3/8/22.
//

#include "../includes/minishell.h"

void print_header(void)
{
	printf ("\n");
	printf ("\e[1;34m");
	printf ("#####################################################\n");
	printf("\e[1;34m   ___  _____   __  __\e[0;36m               _          _ _\n");
	printf("\e[1;34m  /   |/ __  \\ |  \\/  \e[0;36m(_)     (_)   | |        | | |\n");
	printf("\e[1;34m / /| |`' / /' | .  . |\e[0;36m_ _ __  _ ___| |__   ___| | |\n");
	printf("\e[1;34m/ /_| |  / /   | |\\/| |\e[0;36m | '_ \\| / __| '_ \\ / _ \\ | |\n");
	printf("\e[1;34m\\___  |./ /___ | |  | |\e[0;36m | | | | \\__ \\ | | |  __/ | |\n");
	printf("\e[1;34m    |_/\\_____/ \\_|  |_/\e[0;36m_|_| |_|_|___/_| |_|\\___|_|_|\n");
	printf ("\e[1;34m\n");
	printf ("#####################################################\n");
	printf ("\e[0m");
	printf ("\e[0;36m By\e[1;34m plefevre\e[0;36m &\e[1;34m lcalvie\n");
	printf ("\e[0m");
	printf ("\n");


}