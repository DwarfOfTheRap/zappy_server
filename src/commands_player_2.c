#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, PREND);
	if (!p->actions->size)
		pre_action_prend(var, p, &t);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> prend %s\n", p->id, args);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, POSE);
	if (!p->actions->size)
		pre_action_pose(var, p, &t);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> pose %s\n", p->id, args);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, BROADCAST);
	if (!p->actions->size)
		pre_action_broadcast(var, p, &t);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> broadcast %s\n", p->id,
				args);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	(void)args;
	(void)var;
	action_add_wrapper(var, p, &t, CONNECT_NBR);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> connect_nbr\n", p->id);
}
