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

void		lst_delete_content(t_lst_head *h, void *content)
{
	t_lst_elem	*e;

	if (!h)
		return ;
	e = h->first;
	while (e && e->content != content)
		e = e->next;
	if (e)
	{
		lst_remove(h, e);
		free(e);
	}
}

void		action_player_clear(t_player *player, t_zappy *var)
{
	t_lst_head	*list;

	list = &var->actions;
	lst_free_match(list, player, cmp, action_free);
	player->pending_actions = 0;
}

t_action	*get_first_action(t_lst_head *list)
{
	t_lst_elem	*elem;

	if (!list)
		return (NULL);
	if ((elem = list->first))
		return ((elem->content) ? (t_action *)elem->content : NULL);
	return (NULL);
}

t_action	*get_last_action(t_lst_head *list)
{
	t_lst_elem	*elem;

	if (!list)
		return (NULL);
	if ((elem = list->last))
		return ((elem->content) ? (t_action *)elem->content : NULL);
	return (NULL);
}
