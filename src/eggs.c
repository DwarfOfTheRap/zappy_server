#include "serveur.h"

void			egg_add_wrapper(t_zappy *var, t_player *p)
{
	t_egg		*new_egg;
	t_tstmp		time[2];

	time[0] = var->start_time;
	time[1] = time_generate(600, time[0], var);
	new_egg = egg_create(p, var, time);
	if (!egg_add(new_egg, var))
		free(new_egg);
}
