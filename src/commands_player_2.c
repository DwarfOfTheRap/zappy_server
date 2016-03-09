#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const char	g_ressources[7][16];

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, PREND);
	message_gfx_pgt(var, p, 0);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> prend %s\n", p->id, args);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, POSE);
	message_gfx_pdr(var, p, 0);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> pose %s\n", p->id, args);
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, EXPULSE);
	message_gfx_pex(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> expulse %s\n", p->id, args);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, BROADCAST);
	message_gfx_pbc(var, p, args);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> broadcast %s\n", p->id, args);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	(void)var;
	message_player_connect_nbr(p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> connect_nbr %s\n", p->id, args);
}
