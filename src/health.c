#include <stdio.h>//
#include <stdlib.h>
#include "serveur.h"

void		check_players_life(t_zappy *var)
{
	int	i;

	i = 3;
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT
			&& var->players[i].timeofdeath.tv_sec
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
	p->level = 1;
	p->coord[0] = rand() % var->board_size[0];
	p->coord[1] = rand() % var->board_size[1];
	p->facing = rand() % 4;
}

void		player_die(t_player *p)
{
	p->status = FD_CLOSE;
	message_player_mort(p);
}

void		player_eat(t_player *p, t_zappy *var)
{
	p->timeofdeath = time_generate(126, p->timeofdeath, var);
}

void		player_vomit(t_player *p, t_zappy *var)
{
	t_tstmp ref;

	ref.tv_sec = 0;
	ref.tv_usec = 0;
	p->timeofdeath = time_sub(time_generate(126, ref, var), p->timeofdeath);
}
