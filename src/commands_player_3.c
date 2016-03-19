#include <string.h>
#include "serveur.h"

extern int			g_log;
extern const int	g_incant[7][7];

void	command_fork(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "fork");
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	if (!p->pending_actions)
		pre_action_fork(var, p, NULL);
	action_add_wrapper(var, p, &t, FORK);
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

	i = 4;
	nb_player = 0;
	while (i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT &&
			var->players[i].level == p->level &&
			same_square(var->players[i].coord, p->coord))
		{
			++pl[i];
			++nb_player;
		}
		++i;
	}
	return (nb_player);
}

void	command_incantation_notification(t_zappy *var, t_player *p,
		t_aargs *args)
{
	int			i;
	t_player	*p2;
	t_action	*a;

	i = 3;
	while (++i <= *var->fd_max)
	{
		if (args->pl[i])
		{
			p2 = &var->players[i];
			if (p2 != p && p2->pending_actions)
			{
				a = find_player_first_action(p2, var);
				if (a && (a->run == &action_player_avance ||
						a->run == &action_player_droite ||
						a->run == &action_player_gauche))
					message_gfx_ppo(var, p2);
				message_player_ko(p2);
				action_player_clear(p2, var);
			}
			p2->pending_actions = (p2 == p) ? 9 : 10;
			message_player_incantation_start(p2);
		}
	}
}

void	command_incantation(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "incantation");
	bzero(&t, sizeof(t_aargs));
	if (!p->pending_actions)
		pre_action_incantation(var, p, &t);
	action_add_wrapper(var, p, &t, INCANTATION);
}
