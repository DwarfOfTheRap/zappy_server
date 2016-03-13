#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

extern const t_action_d	g_action[12];
extern int				g_log;

static int	action_find_ref(t_action *action)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (g_action[i].f == action->run)
			return (g_action[i].rel_time);
		i++;
	}
	return (-1);
}

void		compute_action_new_time(t_action *action, t_zappy *var)
{
	double	old_start;
	double	old_end;
	double	current;
	int		ref;
	float	ratio;

	old_start = time_double(action->creation_t);
	old_end = time_double(action->trigger_t);
	current = time_double(var->start_time);
	ratio = (1 - (current - old_start) / (old_end - old_start));
	if ((ref = action_find_ref(action)) < 0)
	{
		if (g_log & LOG_E)
			printf("[\033[0;31mERROR\033[0m] update_tick can't find ref time\n");
		return ;
	}
	old_start = (ref / (double)var->tick) * 1000000 * ratio;
	action->trigger_t = time_create(current + old_start);
	action->creation_t = var->start_time;
}

void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var)
{
	double	death_ref;

	death_ref = time_elapsed(var->start_time, p->timeofdeath) / 1000000 * old_tick;
	p->timeofdeath = time_generate(death_ref, var->start_time, var);
}
