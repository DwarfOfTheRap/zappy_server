#include "serveur.h"

int			count_player_actions(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;
	int			nb;

	if ((!p && var))
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
	t_action	*final_action;

	// TODO:
	// CHECK PENDING_ACTIONS DURING LOOP TO STOP ITERATING IF WE ALREADY FOUND IT
	if (!(p && var) || !p->pending_actions)
		return (NULL);
	list = &var->actions;
	final_action = NULL;
	action = NULL;
	cursor = list->first;
	while (cursor)
	{
		if ((action = (t_action*)cursor->content) && action->player == p)
			final_action = action;
		cursor = cursor->next;
	}
	return (final_action);
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
