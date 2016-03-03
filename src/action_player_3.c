#include "serveur.h"

void	action_player_incantation(t_zappy *var, t_player *p, char *args)
{
	(void)var;
	(void)args;
	++p->level;
	message_player_incantation_end(p);
}

void	action_player_fork(t_zappy *var, t_player *p, char args)
{
	(void)args;
	(void)var;
	// add new egg on player coordinate
	message_player_ok(p);
}
