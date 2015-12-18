#include <stdlib.h>
#include <string.h>
#include "server.h"

int		main(int ac, const char **av)
{
	int			ret;
	t_arguments	args;
	t_zappy		game_var;

	bzero(&args, sizeof(args));
	if ((ret = read_arguments(ac, av, &args)))
		exit_arg_error(ret, &args);
	init(&game_var, &args);
	return (0);
}
