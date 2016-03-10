#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const int	g_incant[7][7];

void	action_player_incantation(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 3;
	message_gfx_pie(var, p, args->pl[0]);
	if (args->pl[0])
	{
		while (i <= *(var->fd_max))
		{
			if (args->pl[i])
			{
				++var->players[i].level;
				message_player_incantation_end(&var->players[i]);
				message_gfx_plv(var, &var->players[i]);
			}
			++i;
		}
		dispatch_incantation_ressources(var, p, g_incant[p->level - 2]);
	}
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d incantation", p->id);
}

void	action_player_fork(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)args;
	(void)var;
	// add new egg on player coordinate
	message_player_ok(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d fork\n", p->id);
}

void	action_player_connect_nbr(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)var;
	(void)args;
	message_player_connect_nbr(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d connect_nbr\n", p->id);
}
