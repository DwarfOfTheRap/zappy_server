#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "serveur.h"

int		check_error_int(char *str, int value)
{
	dprintf(2, "%s %d not in range.\n", str, value);
	return (1);
}

int		check_team_names_characters(t_arguments *args)
{
	u_int	i;
	u_int	j;
	int		error;
	char	*name;

	if (!args->teams)
		return (1);
	error = 0;
	i = 0;
	while (i < args->nb_team - 1)
	{
		j = 0;
		name = args->teams[i].name;
		while (name[j])
		{
			if (!isalnum(name[j]) && name[j] != '_' && name[j] != ' ')
				++error;
			++j;
		}
		++i;
	}
	if (error)
		dprintf(2, "Some team have invalid character in name\n");
	return (error);
}

int		check_team_names(t_arguments *args)
{
	u_int	i;
	u_int	j;
	int		error;

	if (!args->teams)
		return (1);
	i = 0;
	error = 0;
	while (i < args->nb_team - 1)
	{
		j = i + 1;
		while (j < args->nb_team)
		{
			if (!strcmp(args->teams[i].name, args->teams[j].name))
				++error;
			++j;
		}
		++i;
	}
	if (error)
		dprintf(2, "Some teams share the same name\n");
	return (error);
}

int		check_arguments(t_arguments *args, int error)
{
	if (args->port < MIN_PORT || args->port > MAX_PORT)
		error += check_error_int("Port", args->port);
	if (args->width < MIN_MAP || args->width > MAX_MAP)
		error += check_error_int("Width", args->width);
	if (args->height < MIN_MAP || args->height > MAX_MAP)
		error += check_error_int("Height", args->height);
	if (args->nb_clients < MIN_CLIENT || (args->nb_team &&
				args->nb_clients > (MAX_FD - 4) / (int)args->nb_team))
		error += check_error_int("Number of client", args->nb_clients);
	if (args->tick < MIN_TICK || args->tick > MAX_TICK)
		error += check_error_int("Tick", args->tick);
	if (!args->nb_team)
	{
		++error;
		dprintf(2, "No team provided\n");
	}
	else
	{
		error += check_team_names(args);
		error += check_team_names_characters(args);
	}
	return (error);
}
