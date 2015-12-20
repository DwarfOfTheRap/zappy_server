#include <stdlib.h>
#include <string.h>
#include "serveur.h"

int		main(int ac, const char **av)
{
	int			ret;
	t_arguments	args;
	t_zappy		game_var;
	t_server	serv;

	bzero(&args, sizeof(args));
	if ((ret = read_arguments(ac, av, &args)))
		exit_arg_error(ret, &args);
	if (!init(&game_var, &serv, &args))
		ret = ret;// let's play
	return (0);
}
