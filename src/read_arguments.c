#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int		z_error(char *str)
{
	dprintf(2, "%s\n", str);
	return (1);
}

int		get_opt(const char *str)
{
	int			j;
	const char	arg[6][3] = {"-p", "-x", "-y", "-c", "-t", "-n"};

	j = 0;
	while (j < 6 && strcmp(arg[j], str))
		++j;
	return (j);
}

int		get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args)
{
	int		first;
	int		j;

	++(*i);
	first = *i;
	if (args->nb_team > 0)
		rm_teams(&(args->teams), &(args->nb_team));
	while (*i < m_arg.ac && get_opt(m_arg.av[*i]) == 6)
		++(*i);
	if (*i == first)
		return (z_error("No team's name given"));
	args->nb_team = *i - first;
	if (!(args->teams = (t_team *)malloc(sizeof(t_team) * args->nb_team)))
		return (z_error("Can't allocate memory"));
	j = 0;
	while (first < *i)
	{
		args->teams[j].name = strdup(m_arg.av[first]);
		++first;
		++j;
	}
	return (0);
}

int		get_opt_int(t_main_arg const m_arg, int *i, int arg, t_arguments *args)
{
	int			j;
	const char	*str = m_arg.av[*i + 1];

	*i += 1;
	j = 0;
	if (get_opt(str) != 6)
	{
		dprintf(2, "%s: missing argument\n", m_arg.av[*i - 1]);
		return (1);
	}
	*i += 1;
	while (str[j] && str[j] >= '0' && str[j] <= '9')
		++j;
	if (str[j] != 0)
	{
		dprintf(2, "%s %s: invalid argument\n", m_arg.av[*i - 2], str);
		return (1);
	}
	*(&(args->port) + arg) = atoi(str);
	return (0);
}

int		read_arguments(int ac, char const **av, t_arguments *args)
{
	int					i;
	int					ret;
	int					error;
	const t_main_arg	m_arg = {ac, av};

	i = 1;
	error = 0;
	while (i < ac)
	{
		ret = get_opt(av[i]);
		if (ret < 5)
			error += get_opt_int(m_arg, &i, ret, args);
		else if (ret == 5)
			error += get_opt_string(m_arg, &i, args);
		else
		{
			dprintf(2, "%s: unrecognised option\n", av[i]);
			++error;
			++i;
		}
	}
	return (check_arguements(args, error));
}
