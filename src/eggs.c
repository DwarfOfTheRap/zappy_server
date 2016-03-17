#include "serveur.h"

void	check_eggs(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_egg		*egg;

	list = &var->eggs;
	cursor = list->first;
	while (cursor)
	{
		egg = (t_egg*)cursor->content;
		if (time_compare(egg->hatching_time, var->start_time))
			// eclosion
			;
		cursor = cursor->next;
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
