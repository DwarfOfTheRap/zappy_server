#include <stdlib.h>
#include <string.h>
#include "serveur.h"

int		main(int ac, const char **av)
{
	int			ret;
	t_arguments	args;
	t_zappy		*var;
	t_server	serv;

	bzero(&args, sizeof(args));
	if (!(var = (t_zappy *)malloc(sizeof(t_zappy))))
		return (1);
	if ((ret = read_arguments(ac, av, &args)))
		exit_arg_error(ret, &args);
	if (!init(var, &serv, &args))
		main_loop(var, &serv);
	cleanup_game(var, &serv);
	free(var);
	return (0);
}
