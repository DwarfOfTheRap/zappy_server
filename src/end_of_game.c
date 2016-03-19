#include "serveur.h"

extern int	g_continue;

void	disconnect_loser(t_zappy *var, t_team *team)
{
	int			i;
	t_player	*p;

	i = 4;
	while (i <= *var->fd_max)
	{
		p = &var->players[i];
		if (p->status == FD_CLIENT && (p->team != team || p->level != 8))
			player_die(var, p);
		++i;
	}
}

void	check_if_team_win(t_zappy *var, t_server *serv)
{
	int			i;

	i = 0;
	while (!var->game_won && i < var->nb_team - 1)
	{
		if (var->teams[i].max_level >= 6)
		{
			message_gfx_seg(var, NULL, &var->teams[i]);
			disconnect_loser(var, &var->teams[i]);
			var->game_won = 1;
		}
		++i;
	}
	if (var->game_won && g_continue)
	{
		g_continue = 0;
		i = 4;
		while (i <= serv->fd_max)
		{
			g_continue = (var->players[i].status == FD_CLIENT) ? 1 : g_continue;
			++i;
		}
	}
}
