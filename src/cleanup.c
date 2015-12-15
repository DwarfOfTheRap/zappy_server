#include <stdlib.h>
#include "server.h"

void	rm_teams(t_team **teams, u_int *nb_team)
{
	while ((*nb_team)-- > 0)
		free((*teams[*nb_team]).name);
	free(*teams);
	*teams = NULL;
}
