#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

int			get_opt_verbose(t_main_arg const m_arg, int *i)
{
	int			j;
	int			error;
	char		*ret;
	const char	arg[7] = "weicap";

	++(*i);
	if (*i >= m_arg.ac || get_opt(m_arg.av[*i]) != 7)
		return (z_error("-v: missing argument"));
	j = 0;
	error = 0;
	while (m_arg.av[*i][j])
	{
		if ((ret = strchr(arg, m_arg.av[*i][j])))
			g_log += 1 << (ret - arg);
		else
			++error;
		++j;
	}
	++(*i);
	if (error)
		dprintf(2, "-v: invalid option\n");
	return (error);
}
