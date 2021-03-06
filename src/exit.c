#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

void	exit_arg_error(int error, t_arguments *args)
{
	if (error > 0)
		dprintf(2, "\033[1;31m%d\033[0m errors !\n\n", error);
	if (args->nb_team > 0)
		rm_teams(&(args->teams), (int *)&(args->nb_team));
	usage();
	exit(EXIT_FAILURE);
}
