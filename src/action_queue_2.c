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
	t_lst_head	*list_p;

	list = var->actions;
	list_p = player->actions;
	lst_free_match(list, player, cmp, action_free);
	lst_delete(list_p, action_free);
	player->pending_actions = 0;
}

t_action*	action_player_first(t_player *player, t_zappy *var)
{
	return (lst_first_match(var->actions, player, cmp));
}

t_action	*get_first_action(t_lst_head *list)
{
	t_lst_elem	*elem;

	if (!list)
		return (NULL);
	if ((elem = list->first))
		return ((t_action *)elem->content);
	return (NULL);
}

t_action	*get_last_action(t_lst_head *list)
{
	t_lst_elem	*elem;

	if (!list)
		return (NULL);
	if ((elem = list->first))
		return ((t_action *)elem->content);
	return (NULL);
}
