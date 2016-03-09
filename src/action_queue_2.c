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
}
