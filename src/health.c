#include <stdlib.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void		check_players_life(t_zappy *var)
{
	int	i;

	i = 3;
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT
			&& var->players[i].timeofdeath.tv_sec
			&& time_compare(var->players[i].timeofdeath, var->start_time))
			player_die(var, &var->players[i]);
		i++;
	}
}

void		player_spawn(t_player *p, t_zappy *var)
{
	t_tstmp	timeofdeath;

	timeofdeath = time_generate(1260, var->start_time, var);
	p->timeofdeath = timeofdeath;
	p->level = 1;
	p->pending_actions = 0;
	p->coord[0] = rand() % var->board_size[0];
	p->coord[1] = rand() % var->board_size[1];
	p->facing = rand() % 4;
}

void		player_die(t_zappy *var, t_player *p)
{
	int		i;

	p->status = FD_CLOSE;
	i = 1;
	while (i < 7)
	{
		var->board[p->coord[0]][p->coord[1]][i] += p->inv[i - 1];
		++i;
	}
	message_player_mort(p);
	action_player_clear(p, var);
	if (g_log & LOG_I)
		printf("[\033[0;34mINFO\033[0m] Client %d die\n", p->id);
}

void		player_eat(t_player *p, t_zappy *var)
{
	p->timeofdeath = time_generate(126, p->timeofdeath, var);
}

void		player_vomit(t_player *p, t_zappy *var)
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
