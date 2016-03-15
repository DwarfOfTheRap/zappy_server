#include "serveur.h"

int		get_food_number(t_player *p, t_zappy *var)
{
	unsigned long long	elapsed;

	if (time_compare(p->timeofdeath, var->start_time))
		return (0);
	elapsed = time_elapsed(var->start_time, p->timeofdeath);
	return (elapsed / 126 * var->tick / 1000000);
}
