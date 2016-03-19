#include <stdlib.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const char	g_log_level[7][24];

void				check_players_life(t_zappy *var)
{
	int	i;

	i = 4;
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT
			&& var->players[i].timeofdeath.tv_sec
			&& time_compare(var->players[i].timeofdeath, var->start_time))
			player_die(var, &var->players[i]);
		i++;
	}
}

void				player_spawn(t_player *p, t_zappy *var, int *coord)
{
	static int	unique_id = 1;
	t_tstmp		timeofdeath;

	timeofdeath = time_generate(1260, var->start_time, var);
	p->timeofdeath = timeofdeath;
	p->level = 1;
	p->unique_id = unique_id++;
	p->pending_actions = 0;
	p->coord[0] = (!coord) ? rand() % var->board_size[0] : coord[0];
	p->coord[1] = (!coord) ? rand() % var->board_size[1] : coord[1];
	p->facing = rand() % 4;
}

void				player_die(t_zappy *var, t_player *p)
{
	p->status = FD_CLOSE;
	message_player_mort(p);
	action_player_clear(p, var);
	if (g_log & LOG_I)
		printf("[%s] Client %d (%d) die\n", g_log_level[3], p->id,
				p->unique_id);
}

void				player_eat(t_player *p, t_zappy *var)
{
	p->timeofdeath = time_generate(126, p->timeofdeath, var);
}

void				player_vomit(t_player *p, t_zappy *var)
{
	t_tstmp		ref;
	long long	timeofdeath;
	long long	new_time;

	ref.tv_sec = 0;
	ref.tv_usec = 0;
	timeofdeath = time_long(p->timeofdeath);
	new_time = timeofdeath - time_long(time_generate(126, ref, var));
	p->timeofdeath = time_long_create(new_time);
}
