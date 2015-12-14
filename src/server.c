#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team> "
		"[<team>] [<team>] ... -c <nb> -t <t>");
	printf("-p numero de port");
	printf("-x largeur du Monde");
	printf("-y hauteur du Monde");
	printf("-n <nom equipe 1> <nom equipe 2> ...");
	printf("-c nombre de client autorises au commencement du jeu");
	printf("-t diviseur de l'unite de temps (plus t est grand, plus le "
		"jeu va vite)");
	exit(EXIT_FAILURE);
}

int		main(int ac, const char **av)
{
	t_arguments	args;

	bzero(&args, sizeof(args));
	if (ac <= 12 || read_arguments(ac, av, &args))
		usage();
	return (0);
}
