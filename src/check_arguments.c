#include <stdio.h>
#include "server.h"

int		check_error_int(char *str, int value)
{
	dprintf(2, "%s %d not in range.\n", str, value);
	return (1);
}

int		check_arguements(t_arguments *args, int error)
{
	if (args->port < MIN_PORT || args->port > MAX_PORT)
		error += check_error_int("Port", args->port);
	if (args->width < MIN_MAP || args->width > MAX_MAP)
		error += check_error_int("Width", args->width);
	if (args->height < MIN_MAP || args->height > MAX_MAP)
		error += check_error_int("Height", args->height);
	if (args->nb_clients < MIN_CLIENT || args->nb_clients > MAX_FD - 4)
		error += check_error_int("Number of client", args->nb_clients);
	if (args->tick < MIN_TICK || args->tick > MAX_TICK)
		error += check_error_int("Tick", args->tick);
	return (error);
}
