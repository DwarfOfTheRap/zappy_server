#include "serveur.h"

extern const char	g_ressources[7][16];

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	// add player action to action queue
	message_gfx_pgt(var, p, 0);
	message_gfx_pin(var, p);
	message_gfx_bct(var, p->coord);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	// add player action to action queue
	message_gfx_pdr(var, p, 0);
	message_gfx_pin(var, p);
	message_gfx_bct(var, p->coord);
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_pex(var, p);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	// add player action to action queue
	message_gfx_pbc(var, p, args);
}

void	command_incantation(t_zappy *var, t_player *p, char *args)
{
	int		i;

	(void)args;
	// add player action to action queue
	message_player_incantation_start(p);
	i = 0;
	while (i <= *(var->fd_max))
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
	message_gfx_pic(var, p);
}
