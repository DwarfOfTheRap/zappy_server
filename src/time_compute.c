#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

void		compute_action_new_time(t_action *action, int old_tick, t_zappy *var)
{
	double	action_ref;

	if (!action)
		return ;
	action_ref = time_elapsed(var->start_time, action->trigger_t) / 1000000 * old_tick;
	action->trigger_t = time_generate(action_ref, var->start_time, var);
	action->creation_t = var->start_time;
}

void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var)
{
	double	death_ref;

	if (!p)
		return ;
	death_ref = time_elapsed(var->start_time, p->timeofdeath) / 1000000 * old_tick;
	p->timeofdeath = time_generate(death_ref, var->start_time, var);
}
