#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> prend %s\n", p->id, args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->actions->size)
		pre_action_prend(var, p, &t);
	action_add_wrapper(var, p, &t, PREND);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> pose %s\n", p->id, args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->actions->size)
		pre_action_pose(var, p, &t);
	action_add_wrapper(var, p, &t, POSE);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> broadcast %s\n", p->id,
				args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->actions->size)
		pre_action_broadcast(var, p, &t);
	action_add_wrapper(var, p, &t, BROADCAST);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> connect_nbr\n", p->id);
	bzero(&t, sizeof(t_aargs));
	(void)args;
	(void)var;
	action_add_wrapper(var, p, &t, CONNECT_NBR);
}
