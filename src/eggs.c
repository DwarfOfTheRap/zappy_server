#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void		egg_set_rotten_time(t_egg *egg, t_zappy *var)
{
	egg->laying_time = var->start_time;
	egg->hatching_time = time_generate(1260, var->start_time, var);
}

static void	check_eggs_sub(t_zappy *var)
{
	t_lst_head	*list_hatched;
	t_lst_elem	*elem;
	t_egg		*egg;

	list_hatched = &var->eggs_hatched;
	while ((egg = get_first_egg(list_hatched))
			&& time_compare(egg->hatching_time, var->start_time))
	{
		message_gfx_edi(var, egg);
		egg->team->egg_slot_number--;
		elem = lst_pop(list_hatched, 0);
		lst_delete_elem(&elem, free);
		if (g_log & LOG_I)
			printf("[\033[0;34mINFO\033[0m] Egg %d rot\n", egg->id);
	}
}

void		check_eggs(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_head	*list_hatched;
	t_lst_elem	*elem;
	t_egg		*egg;

	list = &var->eggs;
	list_hatched = &var->eggs_hatched;
	while ((egg = get_first_egg(list))
		&& time_compare(egg->hatching_time, var->start_time))
	{
		message_gfx_eht(var, egg);
		egg->team->egg_slot_number++;
		egg_set_rotten_time(egg, var);
		elem = lst_pop(list, 0);
		lst_pushback(list_hatched, elem);
		if (g_log & LOG_I)
			printf("[\033[0;34mINFO\033[0m] Egg %d hatched\n", egg->id);
	}
	check_eggs_sub(var);
}

t_egg		*egg_add_wrapper(t_zappy *var, t_player *p)
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
