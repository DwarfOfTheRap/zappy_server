#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "serveur.h"

extern t_action_d	g_action[9];

void		process_actions(t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*elem;
	t_action	*action;

	list = var->actions;
	while ((action = get_first_action(list))
			&& time_compare(action->time, var->start_time))
	{
		action->run(var, action->player, &action->arg);
		action->player->pending_actions--;
		elem = lst_pop(list, 0);
		lst_delete_elem(&elem, action_free);
	}
}

static int	cmp(void *data1, void *data2)
{
	t_action	*action1;
	t_action	*action2;

	action1 = (t_action*)data1;
	action2 = (t_action*)data2;
	return (time_compare(action1->time, action2->time) <= 0);
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
		return (1);
	}
	return (0);
}

// MIGHT NEED CHANGES TO MATCH MARC'S USAGE
t_action	*action_create(t_aargs *arg, void (*f)(t_zappy*, t_player*,
				t_aargs*), t_player *player, t_tstmp time)
{
	t_action	*new;

	if (!(new = (t_action*)malloc(sizeof(t_action))))
		return (NULL);
	memcpy(&new->arg, arg, sizeof(t_aargs));
	new->run = f;
	new->player = player;
	new->time = time;
	return (new);
}

void		action_add_wrapper(t_zappy *var, t_player *p, t_aargs *args,
				int act)
{
	t_tstmp		time;
	t_action	*new;

	time = time_generate(g_action[act].rel_time, var);
	new = action_create(args, g_action[act].f, p, time);
	p->pending_actions++;
	action_add(new, var);
}
