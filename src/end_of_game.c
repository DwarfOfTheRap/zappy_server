#include "serveur.h"

extern int	g_continue;

void	check_if_team_win(t_zappy *var, t_server *serv)
{
	int			i;

	i = 0;
	while (!var->game_won && i < var->nb_team - 2)
	{
		if (var->teams[i].max_level >= 6)
		{
			message_gfx_seg(var, &var->teams[i]);
			var->game_won = 1;
		}
		++i;
	}
	if (var->game_won && g_continue)
	{
		g_continue = 0;
		i = 3;
		while (i <= serv->fd_max)
		{
			g_continue = (var->players[i].status == FD_CLIENT) ? 1 : g_continue;
			++i;
		}
	}
}
