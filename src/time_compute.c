#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

long long	compute_new_time(long long trigger, int old_tick, t_zappy *var)
{
	long long	trigger_ref;

	trigger_ref = (trigger - var->start_time) * old_tick / var->tick;
	return (var->start_time + trigger_ref);
}

void		compute_action_new_time(t_action *action, int old_tick,
				t_zappy *var)
{
	if (!action)
		return ;
	action->trigger_t = compute_new_time(action->trigger_t, old_tick, var);
}

void		compute_egg_new_time(t_egg *egg, int old_tick, t_zappy *var)
{
	if (!egg)
		return ;
	egg->hatching_time = compute_new_time(egg->hatching_time, old_tick, var);
}

void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var)
{
	if (!p)
		return ;
	p->timeofdeath = compute_new_time(p->timeofdeath, old_tick, var);
}
