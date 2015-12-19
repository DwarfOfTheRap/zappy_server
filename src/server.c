#include <stdlib.h>
#include <string.h>
#include "server.h"

int		main(int ac, const char **av)
{
	int			ret;
	t_arguments	args;

	bzero(&args, sizeof(args));
	if ((ret = read_arguments(ac, av, &args)))
		exit_arg_error(ret, &args);
	return (0);
}
