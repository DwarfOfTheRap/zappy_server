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
	t_player	*p;

	list = &var->actions;
	while ((action = get_first_action(list))
			&& time_compare(action->trigger_t, var->start_time))
	{
		p = action->player;
		action->run(var, p, &action->arg);
		elem = lst_pop(list, 0);
		lst_delete_elem(&elem, action_free);
		p->pending_actions--;
		if (p->pending_actions)
		{
			action = find_player_first_action(p, var);
			if (action && action->pre)
				action->pre(var, p, &action->arg);
		}
	}
}

static int	cmp(void *data1, void *data2)
{
	t_action	*action1;
	t_action	*action2;

	action1 = (t_action*)data1;
	action2 = (t_action*)data2;
	return (time_compare(action1->trigger_t, action2->trigger_t));
}

int			action_add(t_action *action, t_zappy *var)
{
	t_lst_elem	*new;
	t_player	*p;
	t_action	*last_action;

	p = action->player;
	if (!action || p->pending_actions >= 10)
		return (0);
	if ((new = lst_create_no_malloc(action)))
	{
		last_action = get_last_action(&var->actions);
		if (!last_action || time_compare(last_action->trigger_t,
					action->trigger_t))
			lst_pushback(&var->actions, new);
		else
			lst_insert(&var->actions, new, cmp);
		p->pending_actions++;
		return (1);
	}
	return (0);
}

t_action	*action_create(t_aargs *arg, void (*f)(t_zappy*, t_player*,
				t_aargs*), t_player *player, long long time)
{
	t_action	*new;

	if (!(new = (t_action*)malloc(sizeof(t_action))))
		return (NULL);
	bzero(new, sizeof(t_action));
	memcpy(&new->arg, arg, sizeof(t_aargs));
	new->run = f;
	new->player = player;
	new->trigger_t = time;
	return (new);
}

void		action_add_wrapper(t_zappy *var, t_player *p, t_aargs *args,
								int act)
{
	long long	time[2];
	t_action	*new_action;
	t_action	*last_action;

	last_action = find_player_last_action(p, var);
	if (!last_action)
		time[0] = var->start_time;
	else
		time[0] = last_action->trigger_t;
	time[1] = time_generate(g_action[act].rel_time, time[0], var);
	new_action = action_create(args, g_action[act].f, p, time[1]);
	if (!action_add(new_action, var))
		action_free(new_action);
	else
		new_action->pre = g_action[act].pre;
}
