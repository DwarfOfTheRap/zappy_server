#include <stdio.h>
#include "serveur.h"

void	command_player_avance(t_zappy *var, t_player *p, char *args)
{
	static const int	move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

	(void)args;
	p->coord[0] += move[p->facing][0];
	p->coord[1] += move[p->facing][1];
	if (p->coord[0] < 0)
		p->coord[0] = var->board_size[0] - 1;
	else if (p->coord[0] == var->board_size[0])
		p->coord[0] = 0;
	if (p->coord[1] < 0)
		p->coord[1] = var->board_size[1] - 1;
	else if (p->coord[1] == var->board_size[1])
		p->coord[1] = 0;
	message_player_ok(p);
}

void	command_player_droite(t_zappy *var, t_player *p, char *args)
{
	(void)var;
	(void)args;
	p->facing = (p->facing + 1 == 4) ? 0 : p->facing + 1;
	message_player_ok(p);
}

void	command_player_gauche(t_zappy *var, t_player *p, char *args)
{
	(void)var;
	(void)args;
	p->facing = (p->facing - 1 < 0) ? 3 : p->facing - 1;
	message_player_ok(p);
}

void	command_player_voir_nord(t_zappy *var, t_player *p)
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
		square[0] = ((p->coord[0] + i) + var->board_size[0]) %
			var->board_size[0];
		while (j < count)
		{
			square[1] = ((p->coord[1] - count / 2 + j) + var->board_size[1]) %
				var->board_size[1];
			message_player_voir_square(var, p, square);
			++j;
		}
		add_msg_to_player(p, ", ", 2, 0);
		++i;
	}
}

void	command_player_voir_south(t_zappy *var, t_player *p)
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
		square[0] = ((p->coord[0] - i) + var->board_size[0]) %
			var->board_size[0];
		while (j < count)
		{
			square[1] = ((p->coord[1] - count / 2 + j) + var->board_size[1]) %
				var->board_size[1];
			message_player_voir_square(var, p, square);
			++j;
		}
		add_msg_to_player(p, ", ", 2, 0);
		++i;
	}
}

void	command_player_voir_east(t_zappy *var, t_player *p)
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
		square[1] = ((p->coord[1] + i) + var->board_size[1]) %
			var->board_size[1];
		while (j < count)
		{
			square[0] = ((p->coord[0] - count / 2 + j) + var->board_size[0]) %
				var->board_size[0];
			message_player_voir_square(var, p, square);
			++j;
		}
		add_msg_to_player(p, ", ", 2, 0);
		++i;
	}
}

void	command_player_voir_west(t_zappy *var, t_player *p)
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
		square[1] = ((p->coord[1] - i) + var->board_size[1]) %
			var->board_size[1];
		while (j < count)
		{
			square[0] = ((p->coord[0] - count / 2 + j) + var->board_size[0]) %
				var->board_size[0];
			message_player_voir_square(var, p, square);
			++j;
		}
		add_msg_to_player(p, ", ", 2, 0);
		++i;
	}
}

void	command_player_voir(t_zappy *var, t_player *p, char *args)
{
	void	(* const fun[4])(t_zappy *var, t_player *p) = {
		&command_player_voir_nord, &command_player_voir_east,
		&command_player_voir_south, &command_player_voir_west};

	(void)args;
	add_msg_to_player(p, "{", 1, 0);
	fun[p->facing](var, p);
	add_msg_to_player(p, "}", 1, 1);
}

void	command_player_inventaire(t_zappy *var, t_player *p, char *args)
{
	int		ret;
	char	str[128];

	(void)var;
	(void)args;
	ret = sprintf(str, "{%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d}",
		get_ressource_name(0), 0,
		get_ressource_name(1), p->inv[0],
		get_ressource_name(2), p->inv[1],
		get_ressource_name(3), p->inv[2],
		get_ressource_name(4), p->inv[3],
		get_ressource_name(5), p->inv[4],
		get_ressource_name(6), p->inv[5]);
	add_msg_to_player(p, str, ret, 1);
}
