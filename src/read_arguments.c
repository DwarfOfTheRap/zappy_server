#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

int		z_error(char *str)
{
	dprintf(2, "%s\n", str);
	return (1);
}

int		get_opt(const char *str)
{
	int			j;
	const char	arg[7][4] = {"-p", "-x", "-y", "-c", "-t", "-n", "-v"};

	j = 0;
	while (j < 7 && strcmp(arg[j], str))
		++j;
	return (j);
}

int		get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args)
{
	int		first;
	int		j;

	++(*i);
	first = *i;
	if (args->teams)
		rm_teams(&(args->teams), (int *)&(args->nb_team));
	while (*i < m_arg.ac && get_opt(m_arg.av[*i]) == 7)
		++(*i);
	if (*i == first)
		return (z_error("No team's name given"));
	args->nb_team = *i - first + 1;
	if (!(args->teams = (t_team *)malloc(sizeof(t_team) * args->nb_team)))
		return (z_error("Can't allocate memory"));
	j = 0;
	while (first < *i)
	{
		stpncpy(args->teams[j].name, m_arg.av[first], TEAM_LEN);
		args->teams[j].name[TEAM_LEN] = '\0';
		++first;
		++j;
	}
	stpncpy(args->teams[j].name, "GRAPHIC", TEAM_LEN);
	return (0);
}

int		get_opt_int(t_main_arg const m_arg, int *i, int arg, t_arguments *args)
{
	int			j;
	const char	*str = m_arg.av[*i + 1];

	++(*i);
	j = 0;
	if (*i < m_arg.ac && get_opt(str) != 7)
	{
		dprintf(2, "%s: missing argument\n", m_arg.av[*i - 1]);
		return (1);
	}
	++(*i);
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
		else if (ret == 6)
			error += get_opt_verbose(m_arg, &i);
		else
		{
			dprintf(2, "%s: unrecognised option\n", av[i]);
			++error;
			++i;
		}
	}
	return (check_arguments(args, error));
}
