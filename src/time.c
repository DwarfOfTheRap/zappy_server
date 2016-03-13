#include "serveur.h"

void	update_queue(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;

	list = var->actions;
	cursor = list->first;
	while (cursor)
	{
		action = (t_action *)cursor->content;
		compute_action_new_time(action, var);
		cursor = cursor->next;
	}
}

void	update_player_actions(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;

	list = p->actions;
	cursor = list->first;
	while(cursor)
	{
		action = (t_action *)cursor->content;
		compute_action_new_time(action, var);
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
	old_tick = var->tick;
	var->tick = tick;
	update_queue(var);
	while(i <= *var->fd_max)
	{
		if (var->players[i++].status == FD_CLIENT)
		{
			update_player_actions(&var->players[i], var);
			update_player_timeofdeath(&var->players[i], old_tick, var);
		}
	}
}
