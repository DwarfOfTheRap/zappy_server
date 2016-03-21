#include "serveur.h"

int			count_player_actions(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;
	int			nb;

	if (!(p && var))
		return (-1);
	list = &var->actions;
	nb = 0;
	action = NULL;
	cursor = list->first;
	while (cursor)
	{
		if ((action = (t_action*)cursor->content) && action->player == p)
			++nb;
		cursor = cursor->next;
	}
	return (nb);
}

t_action	*find_player_last_action(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;

	if (!(p && var) || !p->pending_actions)
		return (NULL);
	list = &var->actions;
	action = NULL;
	cursor = list->last;
	while (cursor)
	{
		if ((action = (t_action*)cursor->content) && action->player == p)
			return (action);
		cursor = cursor->prev;
	}
	return (NULL);
}

t_action	*find_player_first_action(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;

	if (!(p && var) || !p->pending_actions)
		return (NULL);
	list = &var->actions;
	action = NULL;
	cursor = list->first;
	while (cursor)
	{
		if ((action = (t_action*)cursor->content) && action->player == p)
			return (action);
		cursor = cursor->next;
	}
	return (NULL);
}

void		reset_players_pending_action_count(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;
	int			i;

	if (!var)
		return ;
	i = 4;
	while (i <= *var->fd_max)
		var->players[i++].pending_actions = 0;
	list = &var->actions;
	action = NULL;
	cursor = list->first;
	while (cursor)
	{
		action = (t_action*)cursor->content;
		++action->player->pending_actions;
		cursor = cursor->next;
	}
}
