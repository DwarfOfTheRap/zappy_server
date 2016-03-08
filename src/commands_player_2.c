#include "serveur.h"

extern const char	g_ressources[7][16];

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, PREND);
	message_gfx_pgt(var, p, 0);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, POSE);
	message_gfx_pdr(var, p, 0);
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, EXPULSE);
	message_gfx_pex(var, p);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, BROADCAST);
	message_gfx_pbc(var, p, args);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	(void)var;
	message_player_connect_nbr(p);
}
