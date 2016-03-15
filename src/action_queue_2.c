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
	t_lst_head	*list_p;
	t_lst_elem	*e;
	t_lst_elem	*en;

	list = &var->actions;
	list_p = &player->actions;
	e = list_p->first;
	while (e)
	{
		en = e->next;
		lst_delete_content(list, e->content);
		action_free(e->content);
		free(e);
		e = en;
	}
	bzero(&player->actions, sizeof(t_lst_head));
}

t_action*	action_player_first(t_player *player, t_zappy *var)
{
	return (lst_first_match(&var->actions, player, cmp));
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
