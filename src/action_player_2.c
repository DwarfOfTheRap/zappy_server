#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const char	g_ressources[7][16];

void	action_player_voir_sub_no(t_zappy *var, t_player *p, int k, int l)
{
	int		i;
	int		j;
	int		count;
	int		square[2];

	i = 0;
	while (i <= p->level)
	{
		j = 0;
		count = (i * 2) + 1;
		square[k] = ((p->coord[k] + (i * l)) + var->board_size[k]) %
			var->board_size[k];
		while (j < count)
		{
			square[!k] = ((p->coord[!k] - count / 2 + j) + var->board_size[!k])
				% var->board_size[!k];
			if (i || j)
				add_msg_to_player(p, ", ", 2, 0);
			message_player_voir_square(var, p, square);
			++j;
		}
		++i;
	}
}

void	action_player_voir_sub_se(t_zappy *var, t_player *p, int k, int l)
{
	int		i;
	int		j;
	int		count;
	int		square[2];

	i = 0;
	while (i <= p->level)
	{
		count = (i * 2) + 1;
		j = count - 1;
		square[k] = ((p->coord[k] + (i * l)) + var->board_size[k]) %
			var->board_size[k];
		while (j >= 0)
		{
			square[!k] = ((p->coord[!k] - count / 2 + j) + var->board_size[!k])
				% var->board_size[!k];
			if (i || j)
				add_msg_to_player(p, ", ", 2, 0);
			message_player_voir_square(var, p, square);
			--j;
		}
		++i;
	}
}

void	action_player_voir(t_zappy *var, t_player *p, t_aargs *args)
{
	int		k;
	int		l;

	(void)args;
	add_msg_to_player(p, "{", 1, 0);
	k = (p->facing == 0 || p->facing == 2) ? 0 : 1;
	l = (p->facing == 0 || p->facing == 1) ? 1 : -1;
	if (p->facing == 0 || p->facing == 3)
		action_player_voir_sub_no(var, p, k, l);
	else
		action_player_voir_sub_se(var, p, k, l);
	add_msg_to_player(p, "}", 1, 1);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d voir\n", p->id);
}

void	action_player_prend(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args->str))
		++i;
	if (i == 7)
		return (message_command_format_error(p, "prend", args->str));
	if (var->board[p->coord[0]][p->coord[1]][i] > 0)
	{
		--var->board[p->coord[0]][p->coord[1]][i];
		if (i == 0)
		{
			player_eat(p, var);
			add_ressource_on_random_square(var, 0);
		}
		else
			++p->inv[i - 1];
		message_player_ok(p);
	}
	else
		message_player_ko(p);
	message_gfx_pin(var, p);
	message_gfx_bct(var, p->coord);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d prend %s\n", p->id, args->str);
}

void	action_player_pose(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args->str))
		++i;
	if (i == 7)
		return (message_command_format_error(p, "pose", args->str));
	// need to replace the hard code one with correct condition relatif to life
	if ((i == 0 && get_food_number(p, var)) || (i > 0 && p->inv[i - 1] > 0))
	{
		if (i == 0)
			player_vomit(p, var);
		else
			--p->inv[i - 1];
		++var->board[p->coord[0]][p->coord[1]][i];
		message_player_ok(p);
	}
	else
		message_player_ko(p);
	message_gfx_pin(var, p);
	message_gfx_bct(var, p->coord);
	if (g_log & LOG_A)
		printf("[\033[0;35mACTION\033[0m] p %d pose %s\n", p->id, args->str);
}
