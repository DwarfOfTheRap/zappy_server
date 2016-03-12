#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const int	g_incant[7][7];

void	command_fork(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, FORK);
	message_gfx_pfk(var, p);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> fork\n", p->id);
}

int		command_incantation_can_incant(t_zappy *var, t_player *p, int nb_player)
{
	int		i;
	int		can_incant;
	int		*square;

	if (p->level == 8)
		return (0);
	square = var->board[p->coord[0]][p->coord[1]];
	can_incant = (nb_player >= g_incant[p->level - 1][0]) ? 1 : 0;
	i = 1;
	while (i < 7)
	{
		if (square[i] < g_incant[p->level - 1][i])
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
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT &&
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

void	command_incantation_notification(t_zappy *var, t_aargs *args)
{
	int			i;
	t_player	*p;
	t_action	*a;

	i = 3;
	while (i <= *(var->fd_max))
	{
		if (args->pl[i])
		{
			p = &var->players[i];
			if (p->actions->size)
			{
				a = p->actions->first->content;
				if (a->run == &action_player_avance ||
						a->run == &action_player_droite ||
						a->run == &action_player_gauche)
					message_gfx_ppo(var, p);
				message_player_ko(p);
				action_player_clear(p, var);
			}
			message_player_incantation_start(p);
		}
		++i;
	}
}

void	command_incantation(t_zappy *var, t_player *p, char *args)
{
	int		nb_player;
	t_aargs	t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	if (!(t.pl = (int *)malloc(sizeof(int) * MAX_FD)))
		return (message_player_ko(p));
	bzero(t.pl, sizeof(int) * MAX_FD);
	nb_player = command_incantation_count_player(var, p, t.pl);
	t.pl[0] = command_incantation_can_incant(var, p, nb_player);
	command_incantation_notification(var, &t);
	action_add_wrapper(var, p, &t, INCANTATION);
	message_gfx_pic(var, p, t.pl);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> incantation\n", p->id);
}
