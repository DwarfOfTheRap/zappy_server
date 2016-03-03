#include "serveur.h"

extern const char	g_ressources[7][16];

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	// send message to gfx_client
	// add player action to action queue
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	// send message to gfx_client
	// add player action to action queue
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// send message to gfx_client
	// add player action to action queue
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	// send message to gfx_client
	// add player action to action queue
}

void	command_incantation(t_zappy *var, t_player *p, char *args)
{
	int		i;

	(void)args;
	// send message to gfx_client
	// add player action to action queue
	message_player_incantation_start(p);
	i = 0;
	while (i < MAX_FD)
	{
		if (var->players[i].status == FD_CLIENT && i != p->id &&
			var->players[i].level == p->level &&
			var->players[i].coord[0] == p->coord[0] &&
			var->players[i].coord[0] == p->coord[0])
		{
			message_player_incantation_start(&var->players[i]);
		}
		++i;
	}
}
