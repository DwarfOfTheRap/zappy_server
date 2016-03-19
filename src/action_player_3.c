#include <stdio.h>
#include <string.h>
#include "serveur.h"

extern int			g_log;
extern const int	g_incant[7][7];
extern const char	g_ressources[7][16];

static void	action_player_incantation_sub(t_zappy *var, t_player *p,
		t_aargs *args)
{
	int		i;
	int		nb_player;

	if (var->game_won)
	{
		args->pl[0] = 0;
		return ;
	}
	i = 4;
	nb_player = 0;
	while (i <= *var->fd_max)
	{
		if (args->pl[i])
		{
			if (var->players[i].status == FD_CLIENT)
				++nb_player;
		}
		++i;
	}
	args->pl[0] = (nb_player >= g_incant[p->level - 1][0]) ? args->pl[0] : 0;
	reset_players_pending_action_count(var);
}

void		action_player_incantation(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 3;
	action_player_incantation_sub(var, p, args);
	message_gfx_pie(var, p, args->pl[0]);
	while (++i <= *var->fd_max)
	{
		if (args->pl[i])
		{
			if (args->pl[0])
			{
				++var->players[i].level;
				if (var->players[i].level == 8)
					++var->players[i].team->max_level;
			}
			message_player_incantation_end(&var->players[i]);
			message_gfx_plv(var, &var->players[i]);
		}
	}
	if (args->pl[0])
		dispatch_incantation_ressources(var, p, g_incant[p->level - 2]);
	if (g_log & LOG_A && args->pl[0])
		log_simple_message(p, LOG_A, "incantation OK");
	if (g_log & LOG_A && !args->pl[0])
		log_simple_message(p, LOG_A, "incantation KO");
}

void		action_player_fork(t_zappy *var, t_player *p, t_aargs *args)
{
	t_egg	*egg;

	(void)args;
	if (!var->game_won)
	{
		egg = egg_add_wrapper(var, p);
		message_gfx_enw(var, egg);
	}
	message_player_ok(p);
	if (g_log & LOG_A)
		log_simple_message(p, LOG_A, "fork");
}

void		action_player_connect_nbr(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)var;
	bzero(args, sizeof(t_aargs));
	message_player_connect_nbr(p);
	if (g_log & LOG_A)
		log_simple_message(p, LOG_A, "connect_nbr");
}

void		action_player_inventaire(t_zappy *var, t_player *p, t_aargs *args)
{
	int		ret;
	char	str[128];

	(void)var;
	(void)args;
	ret = sprintf(str, "{%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d}",
		g_ressources[0], get_food_number(p, var),
		g_ressources[1], p->inv[0],
		g_ressources[2], p->inv[1],
		g_ressources[3], p->inv[2],
		g_ressources[4], p->inv[3],
		g_ressources[5], p->inv[4],
		g_ressources[6], p->inv[5]);
	add_msg_to_player(p, str, ret, 1);
	if (g_log & LOG_A)
		log_simple_message(p, LOG_A, "inventaire");
}
