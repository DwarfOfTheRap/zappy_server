#include "serveur.h"

extern const char	g_ressources[7][16];

void	message_player_ok(t_player *p)
{
	add_msg_to_player(p, "ok", 2, 1);
}

void	message_player_ko(t_player *p)
{
	add_msg_to_player(p, "ko", 2, 1);
}

void	message_player_separator(t_player *p, int sep)
{
	static int	s = 0;

	if (sep && s)
		add_msg_to_player(p, " ", 1, 0);
	s = sep;
}

void	message_player_voir_square_sub(t_zappy *var, t_player *p, int square[2])
{
	int		i;
	int		j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < var->board[square[0]][square[1]][i])
		{
			message_player_separator(p, 1);
			add_msg_to_player(p, g_ressources[i], 0, 0);
			++j;
		}
		++i;
	}
}

void	message_player_voir_square(t_zappy *var, t_player *p, int square[2])
{
	int		i;

	i = 4;
	while (i <= *var->fd_max)
	{
		if (i != p->id && var->players[i].status == FD_CLIENT &&
			var->players[i].coord[0] == square[0] &&
			var->players[i].coord[1] == square[1])
		{
			message_player_separator(p, 1);
			add_msg_to_player(p, "joueur", 6, 0);
		}
		++i;
	}
	message_player_voir_square_sub(var, p, square);
	message_player_separator(p, 0);
}
