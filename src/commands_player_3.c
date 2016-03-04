#include <strings.h>
#include "serveur.h"

extern const int	g_incant[7][7];

void	command_fork(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_pfk(var, p);
}

int		command_incantation_can_incant(t_zappy *var, t_player *p, int nb_player)
{
	int		i;
	int		can_incant;
	int		*square;

	if (p->level == 7)
		return (0);
	square = var->board[p->coord[0]][p->coord[1]];
	can_incant = (nb_player >= g_incant[p->level][0]) ? 1 : 0;
	i = 1;
	while (i < 8)
	{
		if (square[i] < g_incant[p->level][i])
			can_incant = 0;
		++i;
	}
	return (can_incant);
}

int		command_incantation_count_player(t_zappy *var, t_player *p, int *pl)
{
	int		i;
	int		nb_player;

	i = 3;
	nb_player = 0;
	while (i <= *(var->fd_max))
	{
		if (var->players[i].status == FD_CLIENT && i != p->id &&
			var->players[i].level == p->level &&
			var->players[i].coord[0] == p->coord[0] &&
			var->players[i].coord[0] == p->coord[0])
		{
			++pl[i];
			++nb_player;
		}
		++i;
	}
	return (nb_player);
}

void	command_incantation(t_zappy *var, t_player *p, char *args)
{
	int		i;
	int		nb_player;
	int		*pl;

	(void)args;
	if (!(pl = (int *)malloc(sizeof(int) * MAX_FD)))
		return (message_player_ko(p));
	bzero(pl, sizeof(int) * MAX_FD);
	nb_player = command_incantation_count_player(var, p, pl);
	pl[0] = command_incantation_can_incant(var, p, nb_player);
	// add player action to action queue with pl as args
	message_player_incantation_start(p);
	i = 3;
	while (i <= *(var->fd_max))
	{
		if (pl[i])
			message_player_incantation_start(&var->players[i]);
		++i;
	}
	message_gfx_pic(var, p, pl);
}
