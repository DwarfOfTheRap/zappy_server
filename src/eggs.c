#include "serveur.h"

void	check_eggs(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*elem;
	t_egg		*egg;

	list = &var->eggs;
	while ((egg = get_first_egg(list))
		   && time_compare(egg->hatching_time, var->start_time))
	{
		message_gfx_eht(var, egg);
		elem = lst_pop(list, 0);
		lst_delete_elem(&elem, free);
	}
}

t_egg	*egg_add_wrapper(t_zappy *var, t_player *p)
{
	t_egg		*new_egg;
	t_tstmp		time[2];

	time[0] = var->start_time;
	time[1] = time_generate(600, time[0], var);
	new_egg = egg_create(p, var, time);
	if (!egg_add(new_egg, var))
	{
		free(new_egg);
		return (NULL);
	}
	return (new_egg);
}
