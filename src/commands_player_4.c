#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;

void	command_expulse_send_to_gfx(t_zappy *var, t_player *p, t_player *p2,
			t_action *a)
{
	t_player	dummy;

	memcpy(&dummy, p2, sizeof(t_player) - sizeof(t_rcv_buf) -
			sizeof(t_snd_buf));
	if (a && (a->run == &action_player_gauche ||
			a->run == &action_player_droite))
	{
		if (a->run == &action_player_gauche)
			dummy.facing = (dummy.facing - 1 < 0) ? 3 : dummy.facing - 1;
		else if (a->run == &action_player_droite)
			dummy.facing = (dummy.facing + 1 == 4) ? 0 : dummy.facing + 1;
	}
	action_player_move(var, &dummy, p->facing);
	message_gfx_ppo(var, &dummy);
}

int		command_expulse_count_player(t_zappy *var, t_player *p, int *pl)
{
	int			i;
	int			nb_player;
	t_player	*p2;
	t_action	*a;

	i = 3;
	nb_player = 0;
	while (i <= *(var->fd_max))
	{
		p2 = &var->players[i];
		a = NULL;
		if (p2->status == FD_CLIENT && i != p->id &&
			p2->coord[0] == p->coord[0] && p2->coord[0] == p->coord[0] &&
			(!p2->actions->size || ((a = p2->actions->first->content) &&
									a->run != &action_player_avance)))
		{
			if (var->gfx_client)
				command_expulse_send_to_gfx(var, p, p2, a);
			++pl[i];
			++nb_player;
		}
		++i;
	}
	return (nb_player);
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> expulse\n", p->id);
	bzero(&t, sizeof(t_aargs));
	if (!p->actions->size)
		pre_action_expulse(var, p, &t);
	action_add_wrapper(var, p, &t, EXPULSE);
}
