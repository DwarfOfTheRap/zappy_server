#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

t_tstmp		compute_new_time(t_tstmp trigger, int old_tick, t_zappy *var)
{
	long long	trigger_ref;
	long long	start;

	start = time_long(var->start_time);
	trigger_ref = time_elapsed(var->start_time, trigger) * old_tick / var->tick;
	return (time_long_create(start + trigger_ref));
}

void		compute_action_new_time(t_action *action, int old_tick, t_zappy *var)
{
	if (!action)
		return ;
	action->trigger_t = compute_new_time(action->trigger_t, old_tick, var);
	action->creation_t = var->start_time;
}

void		compute_egg_new_time(t_egg *egg, int old_tick, t_zappy *var)
{
	if (!egg)
		return ;
	egg->hatching_time = compute_new_time(egg->hatching_time, old_tick, var);
	egg->laying_time = var->start_time;
}

void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var)
{
	if (!p)
		return ;
	p->timeofdeath = compute_new_time(p->timeofdeath, old_tick, var);
}
