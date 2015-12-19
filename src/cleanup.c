#include <stdlib.h>
#include "server.h"

void	rm_teams(t_team **teams, u_int *nb_team)
{
	if (!*teams)
	{
		*nb_team = 0;
		return ;
	}
	while (*nb_team > 0)
	{
		--(*nb_team);
		free(((*teams)[*nb_team]).name);
	}
	free(*teams);
	*teams = NULL;
}
