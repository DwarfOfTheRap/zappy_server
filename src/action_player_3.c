#include "serveur.h"

void	action_player_incantation(t_zappy *var, t_player *p, char *args)
{
	int		i;
	int		*pl;

	pl = (int *)args;
	i = 3;
	message_gfx_pie(var, p, pl[0]);
	if (pl[0])
	{
		while (i <= *(var->fd_max))
		{
			if (pl[i])
			{
				++var->players[i].level;
				message_player_incantation_end(&var->players[i]);
				message_gfx_plv(var, &var->players[i]);
			}
			++i;
		}
		// dispatch corresponding ressources
	}
}

void	action_player_fork(t_zappy *var, t_player *p, char args)
{
	(void)args;
	(void)var;
	// add new egg on player coordinate
	message_player_ok(p);
}
