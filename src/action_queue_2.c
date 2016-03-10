#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "serveur.h"

static int	cmp(void *data1, void *data2)
{
	t_player	*player;
	t_action	*action;

	player = NULL;
	action = (t_action *)data1;
	if (action)
		player = action->player;
	return (player == data2);
}

void		action_player_clear(t_player *player, t_zappy *var)
{
	t_lst_head	*list;

	list = var->actions;
	lst_free_match(list, player, cmp, free); // change 'free' to 'action_free'
	player->pending_actions = 0;
}

void		check_players_life(t_zappy *var)
{
	int	i;

	i = 0;
	while (i < MAX_FD)
	{
		if (var->players[i].id
			&& time_compare(&var->players[i].timeofdeath, &var->start_time))
		{
			action_player_clear(&var->players[i], var);
			bzero(&var->players[i], sizeof(t_player)); // not sure if correct implementation
		}
		i++;
	}
}
