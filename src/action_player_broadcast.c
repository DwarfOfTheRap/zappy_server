#include <stdio.h>
#include "serveur.h"

extern int	g_log;

int		broadcast_get_distance(int ms[2], int s[2], int r[2], int i)
{
	int		dist;
	int		mid;

	dist = s[i] - r[i];
	mid = ms[i] / 2;
	if (dist >= 0)
		return ((dist > mid) ? dist - ms[i] : dist);
	else
		return ((dist < -mid) ? dist + ms[i] : dist);
}

int		broadcast_get_direction(int ms[2], t_player *s, t_player *r)
{
	int		dist[2];
	int		square;

	dist[0] = broadcast_get_distance(ms, s->coord, r->coord, 0);
	dist[1] = broadcast_get_distance(ms, s->coord, r->coord, 1);
	if (ABS(dist[0]) > ABS(dist[1]))
		square = (dist[0] > 0) ? 1 : 5;
	else if (ABS(dist[0]) < ABS(dist[1]))
		square = (dist[1] > 0) ? 3 : 7;
	else if (dist[0] == 0)
		square = 0;
	else if (dist[0] > 0)
		square = (dist[1] == dist[0]) ? 8 : 2;
	else
		square = (dist[1] == dist[0]) ? 4 : 6;
	return (square);
}

int		broadcast_get_square(int ms[2], t_player *s, t_player *r)
{
	int		absolute_dir;

	absolute_dir = broadcast_get_direction(ms, s, r);
	if (r->facing == 1)
		return ((absolute_dir + 1) % 8 + 1);
	else if (r->facing == 2)
		return ((absolute_dir + 3) % 8 + 1);
	else if (r->facing == 3)
		return ((absolute_dir + 5) % 8 + 1);
	return (absolute_dir);
}

void	action_player_broadcast(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 0;
	while (i < MAX_FD)
	{
		if (i != p->id && var->players[i].status == FD_CLIENT)
			message_player_message(&var->players[i], broadcast_get_square(
				var->board_size, p, &var->players[i]), args->str);
		++i;
	}
	message_player_ok(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d broadcast [%s]\n", p->id,
				args->str);
}
