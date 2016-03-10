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
	t_lst_elem	*elem_p;

	list = var->actions;
	cur_action = (list->first) ? (t_action*)list->first->content : NULL;
	while (list->first && time_compare(&cur_action->trigger_t, start))
	{
		elem = lst_pop(list, 0);
		elem_p = lst_pop(cur_action->player->actions, 0);
		cur_action->run(var, cur_action->player, &cur_action->arg);
		cur_action->player->pending_actions--;
		cur_action = (elem->next) ? (t_action*)elem->next->content : NULL;
		lst_delete_elem(&elem, action_free);
		lst_delete_elem(&elem_p, action_free);
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
		lst_insert(action->player->actions, new, cmp);
		action->player->pending_actions++;
		return (1);
	}
	return (0);
}

t_action	*action_create(t_aargs *arg, void (*f)(t_zappy*, t_player*,
				t_aargs*), t_player *player, t_tstmp *time)
{
	t_action	*new;

	if (!(new = (t_action*)malloc(sizeof(t_action))))
		return (NULL);
	memcpy(&new->arg, arg, sizeof(t_aargs));
	new->run = f;
	new->player = player;
	new->creation_t = time[0];
	new->trigger_t = time[1];
	return (new);
}

void		action_add_wrapper(t_zappy *var, t_player *p, t_aargs *args,
				int act)
{
	t_tstmp		*time;
	t_action	*new;
	t_action	*last;

	time = (t_tstmp*)malloc(sizeof(t_tstmp) * 2);
	//last = (t_action*)p->actions->last;
	last = NULL;
	if (!last || time_compare(&var->start_time, &last->trigger_t))
		time[0] = var->start_time;
	else
		time[0] = last->trigger_t;
	time[1] = time_generate(g_action[act].rel_time, var, time[0]);
	new = action_create(args, g_action[act].f, p, time);
	free(time);
	action_add(new, var);
}
