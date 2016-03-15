#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

void		compute_action_new_time(t_action *action, int old_tick, t_zappy *var)
{
	unsigned long long	action_ref;
	unsigned long long	start;

	if (!action)
		return ;
	start = time_long(var->start_time);
	action_ref = time_elapsed(var->start_time, action->trigger_t) * old_tick / var->tick;
	action->trigger_t = time_long_create(start + action_ref);
	//action->trigger_t = time_generate(action_ref, var->start_time, var);
	action->creation_t = var->start_time;
}

void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var)
{
	unsigned long long	death_ref;
	unsigned long long	start;

	if (!p)
		return ;
	start = time_long(var->start_time);
	death_ref = time_elapsed(var->start_time, p->timeofdeath) * old_tick / var->tick;
	p->timeofdeath = time_long_create(start + death_ref);
	//p->timeofdeath = time_generate(death_ref, var->start_time, var);
	return ;
}
