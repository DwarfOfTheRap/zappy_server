#include <stdlib.h>
#include "serveur.h"

void		check_players_life(t_zappy *var)
{
	int	i;

	i = 0;
	while (i < MAX_FD)
	{
		if (var->players[i].timeofdeath.tv_sec
			&& time_compare(var->players[i].timeofdeath, var->start_time))
			player_die(&var->players[i]);
		i++;
	}
}

void		player_spawn(t_player *p, t_zappy *var)
{
	t_tstmp	timeofdeath;

	timeofdeath = time_generate(1260, var->start_time, var);
	p->timeofdeath = timeofdeath;
}

void		player_die(t_player *p)
{
	p->status = FD_CLOSE;
	message_player_mort(p);
}
