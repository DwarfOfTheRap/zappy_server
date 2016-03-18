#include <string.h>
#include "serveur.h"

extern int			g_log;

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		log_message_str(p, LOG_C, "prend", args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->pending_actions)
		pre_action_prend(var, p, &t);
	action_add_wrapper(var, p, &t, PREND);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		log_message_str(p, LOG_C, "pose", args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->pending_actions)
		pre_action_pose(var, p, &t);
	action_add_wrapper(var, p, &t, POSE);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		log_message_str(p, LOG_C, "broadcast", args);
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->pending_actions)
		pre_action_broadcast(var, p, &t);
	action_add_wrapper(var, p, &t, BROADCAST);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "connect_nbr");
	bzero(&t, sizeof(t_aargs));
	(void)args;
	(void)var;
	action_add_wrapper(var, p, &t, CONNECT_NBR);
}
