#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "serveur.h"

extern t_action_d	g_action[9];

void		process_actions(t_tstmp *start, t_zappy *var)
{
	t_lst_head	*list;
	t_action	*cur_action;
	t_lst_elem	*elem;

	list = var->actions;
	cur_action = (list->first) ? (t_action*)list->first->content : NULL;
	while (list->first && time_compare(&cur_action->trigger_t, start))
	{
		elem = lst_pop(list, 0);
		cur_action->run(var, cur_action->player, cur_action->arg);
		cur_action->player->pending_actions--;
		cur_action = (elem->next) ? (t_action*)elem->next->content : NULL;
		lst_delete_elem(&elem, free);
	}
}

static int	cmp(void *data1, void *data2)
{
	t_action	*action1;
	t_action	*action2;

	action1 = (t_action*)data1;
	action2 = (t_action*)data2;
	return (time_compare(&action1->trigger_t, &action2->trigger_t));
}

int			action_add(t_action *action, t_zappy *var)
{
	t_lst_elem	*new;

	if (!action || action->player->pending_actions >= 10)
		return (0);
	new = lst_create(action, sizeof(t_action));
	if (new)
	{
		lst_insert(var->actions, new, cmp);
		action->player->pending_actions++;
		return (1);
	}
	return (0);
}

// MIGHT NEED CHANGES TO MATCH MARC'S USAGE
t_action	*action_create(char *arg, void (*f)(t_zappy*, t_player*, char*)
							, t_player *player, t_tstmp time)
{
	t_action	*new;

	if (!(new = (t_action*)malloc(sizeof(t_action))))
		return (NULL);
	new->arg = arg;
	new->run = f;
	new->player = player;
	new->trigger_t = time;
	return (new);
}

void		action_add_wrapper(t_zappy *var, t_player *p, char *args, int act)
{
	t_tstmp		time;
	t_action	*new;

	time = time_generate(g_action[act].rel_time, var);
	new = action_create(args, g_action[act].f, p, time);
	action_add(new, var);
}
