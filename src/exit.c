#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void	exit_arg_error(int error, t_arguments *args)
{
	if (error > 0)
		dprintf(2, "\e[1;31m%d\e[0m errors !\n\n", error);
	if (args->nb_team > 0)
		rm_teams(&(args->teams), (int *)&(args->nb_team));
	usage();
	exit(EXIT_FAILURE);
}
