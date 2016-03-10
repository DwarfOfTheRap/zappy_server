#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const int	g_move[4][2];

void	action_player_move(t_zappy *var, t_player *p, int dir)
{
	p->coord[0] += g_move[dir][0];
	p->coord[1] += g_move[dir][1];
	if (p->coord[0] < 0)
		p->coord[0] = var->board_size[0] - 1;
	else if (p->coord[0] == var->board_size[0])
		p->coord[0] = 0;
	if (p->coord[1] < 0)
		p->coord[1] = var->board_size[1] - 1;
	else if (p->coord[1] == var->board_size[1])
		p->coord[1] = 0;
}

void	action_player_avance(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)args;
	action_player_move(var, p, p->facing);
	message_player_ok(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d avance\n", p->id);
}

void	action_player_droite(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)var;
	(void)args;
	p->facing = (p->facing + 1 == 4) ? 0 : p->facing + 1;
	message_player_ok(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d droite\n", p->id);
}

void	action_player_gauche(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)var;
	(void)args;
	p->facing = (p->facing - 1 < 0) ? 3 : p->facing - 1;
	message_player_ok(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d gauche\n", p->id);
}

void	action_player_expulse(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;
	int		has_expulse;

	(void)args;
	i = 0;
	has_expulse = 0;
	while (i < *var->fd_max)
	{
		if (i != p->id && var->players[i].status == FD_CLIENT &&
			var->players[i].coord[0] == p->coord[0] &&
			var->players[i].coord[1] == p->coord[1])
		{
			action_player_move(var, &var->players[i], p->facing);
			message_player_expulsed(p, &var->players[i]);
			// if any action in progress, interrupt it
			++has_expulse;
		}
		++i;
	}
	if (has_expulse)
		message_player_ok(p);
	else
		message_player_ko(p);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d expulse\n", p->id);
}
