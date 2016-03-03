#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern const char	g_ressources[7][16];

void	action_player_voir_sub(t_zappy *var, t_player *p, int k, int l)
{
	int		i;
	int		j;
	int		count;
	int		square[2];

	i = 0;
	while (i < p->level)
	{
		j = 0;
		count = (i * 2) + 1;
		square[k] = ((p->coord[k] + (i * l)) + var->board_size[k]) %
			var->board_size[k];
		while (j < count)
		{
			square[!k] = ((p->coord[!k] - count / 2 + j) + var->board_size[!k])
				% var->board_size[!k];
			message_player_voir_square(var, p, square);
			++j;
		}
		add_msg_to_player(p, ", ", 2, 0);
		++i;
	}
}

void	action_player_voir(t_zappy *var, t_player *p, char *args)
{
	int		k;
	int		l;

	(void)args;
	add_msg_to_player(p, "{", 1, 0);
	k = (p->facing == 0 || p->facing == 2) ? 0 : 1;
	l = (p->facing == 0 || p->facing == 1) ? 1 : -1;
	action_player_voir_sub(var, p, k, l);
	add_msg_to_player(p, "}", 1, 1);
}

void	action_player_inventaire(t_zappy *var, t_player *p, char *args)
{
	int		ret;
	char	str[128];

	(void)var;
	(void)args;
	ret = sprintf(str, "{%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d}",
		g_ressources[0], 0,
		g_ressources[1], p->inv[0],
		g_ressources[2], p->inv[1],
		g_ressources[3], p->inv[2],
		g_ressources[4], p->inv[3],
		g_ressources[5], p->inv[4],
		g_ressources[6], p->inv[5]);
	add_msg_to_player(p, str, ret, 1);
}

void	action_player_prend(t_zappy *var, t_player *p, char *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args))
		++i;
	if (i == 7)
		message_command_format_error(p);
	if (var->board[p->coord[0]][p->coord[1]][i] > 0)
	{
		--var->board[p->coord[0]][p->coord[1]][i];
		if (i == 0)
			; // need to add life to player
		else
			++p->inv[i - 1];
		message_player_ok(p);
	}
	else
		message_player_ko(p);
}

void	action_player_pose(t_zappy *var, t_player *p, char *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args))
		++i;
	if (i == 7)
		message_command_format_error(p);
	// need to replace the hard code one with correct condition relatif to life
	if ((i == 0 && 1) && (i > 0 && p->inv[i - 1] > 0))
	{
		if (i == 0)
			; // remove life to player
		else
			--p->inv[i - 1];
		++var->board[p->coord[0]][p->coord[1]][i];
		message_player_ok(p);
	}
	else
		message_player_ko(p);
}
