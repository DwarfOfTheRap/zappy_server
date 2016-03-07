#include <stdlib.h>
#include <sys/time.h>
#include "serveur.h"
#include "linked_lists.h"

void	process_actions(t_tstmp *start, t_zappy *var)
{
	t_lst_head	*list;
	t_action	*cur_action;
	t_lst_elem	*elem;

	list = var->actions;
	cur_action = (list->first) ? (t_action*)list->first->content : NULL;
	while (list->first && time_compare(&cur_action->time, start) <= 0)
	{
		elem = lst_pop(list, 0);
		cur_action->run(cur_action->player); // ret ?
		cur_action->player->pending_actions--;
		cur_action = (elem->next) ? (t_action*)elem->next->content : NULL;
	}
}

static int	cmp(void *data1, void *data2)
{
	t_action	*action1;
	t_action	*action2;

	action1 = (t_action*)data1;
	action2 = (t_action*)data2;
	return (time_compare(&action1->time, &action2->time) <= 0);
}

int		action_add(t_action *action, t_zappy *var)
{
	t_lst_elem	*new;

	if (action->player->pending_actions >= 10)
		return (0);
	new = lst_create(action, sizeof(t_action));
	if (new)
	{
		lst_insert(var->actions, new, cmp);
		return (1);
	}
	return (0);
}
