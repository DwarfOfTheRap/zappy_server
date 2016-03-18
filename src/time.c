#include "serveur.h"
#include <stdio.h>

void	update_queue(int old_tick, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;

	list = &var->actions;
	cursor = list->first;
	while (cursor)
	{
		action = (t_action *)cursor->content;
		compute_action_new_time(action, old_tick, var);
		cursor = cursor->next;
	}
}

void	update_eggs(int old_tick, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_egg		*egg;

	list = &var->eggs;
	cursor = list->first;
	while (cursor)
	{
		egg = (t_egg *)cursor->content;
		compute_egg_new_time(egg, old_tick, var);
		cursor = cursor->next;
	}
	list = &var->eggs_hatched;
	cursor = list->first;
	while (cursor)
	{
		egg = (t_egg *)cursor->content;
		compute_egg_new_time(egg, old_tick, var);
		cursor = cursor->next;
	}
}

void	update_player_timeofdeath(t_player *p, int old_tick, t_zappy *var)
{
	compute_death_new_time(p, old_tick, var);
}

void	zappy_update_tick(int tick, t_zappy *var)
{
	int	old_tick;
	int	i;

	i = 3;
	if (tick == var->tick)
		return ;
	old_tick = var->tick;
	var->tick = tick;
	update_queue(old_tick, var);
	update_eggs(old_tick, var);
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT)
			update_player_timeofdeath(&var->players[i], old_tick, var);
		i++;
	}
}
