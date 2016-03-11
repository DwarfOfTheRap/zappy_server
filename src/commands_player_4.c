#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;

void	command_expulse_send_to_gfx(t_zappy *var, t_player *p, t_action *a)
{
	t_player	dummy;

	if (!a || a->run != &action_player_gauche ||
			a->run != &action_player_droite)
		message_gfx_ppo(var, p);
	else
	{
		memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) -
				sizeof(t_snd_buf));
		if (a->run == &action_player_gauche)
			dummy.facing = (dummy.facing - 1 < 0) ? 3 : dummy.facing - 1;
		else if (a->run == &action_player_droite)
			dummy.facing = (dummy.facing + 1 == 4) ? 0 : dummy.facing + 1;
		message_gfx_ppo(var, &dummy);
	}
}

int		command_expulse_count_player(t_zappy *var, t_player *p, int *pl)
{
	int			i;
	int			nb_player;
	t_action	*a;

	i = 3;
	nb_player = 0;
	while (i <= *(var->fd_max))
	{
		if (var->players[i].status == FD_CLIENT && i != p->id &&
			var->players[i].coord[0] == p->coord[0] &&
			var->players[i].coord[0] == p->coord[0] &&
			(!(a = action_player_first(&var->players[i], var)) ||
			(a && a->run != &action_player_avance)))
		{
			++pl[i];
			++nb_player;
			if (var->gfx_client)
				command_expulse_send_to_gfx(var, &var->players[i], a);
		}
		++i;
	}
	return (nb_player);
}

void	command_expulse(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	(void)args;
	message_gfx_pex(var, p);
	t.nb = command_expulse_count_player(var, p, t.pl);
	action_add_wrapper(var, p, &t, EXPULSE);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> expulse\n", p->id);
}