#include "serveur.h"

void	command_fork(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_pfk(var, p);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	(void)var;
	message_player_connect_nbr(p);
}
