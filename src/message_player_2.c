#include <stdio.h>
#include "serveur.h"

void	message_player_expulsed(t_player *pusher, t_player *pushed)
{
	int		ret;
	int		square;
	char	str[32];

	square = (((pushed->facing - pusher->facing + 6) % 4) * 2) + 1;
	square = (square < 0) ? square + 8 : square;
	ret = sprintf(str, "deplacement %d", square);
	add_msg_to_player(pushed, str, ret, 1);
}

void	message_player_message(t_player *p, int square, char *msg)
{
	int		ret;
	char	str[32];

	ret = sprintf(str, "message %d,", square);
	add_msg_to_player(p, str, ret, 0);
	add_msg_to_player(p, msg, 0, 1);
}

void	message_player_incantation_start(t_player *p)
{
	add_msg_to_player(p, "elevation en cours", 0, 1);
}

void	message_player_incantation_end(t_player *p)
{
	int		ret;
	char	str[32];

	ret = sprintf(str, "niveau actuel : %d", p->level + 1);
	add_msg_to_player(p, str, ret, 1);
}

void	message_player_connect_nbr(t_player *p)
{
	int		ret;
	char	str[32];

	if (!p->team)
		ret = sprintf(str, "%d", 0);
	else
		ret = sprintf(str, "%d", p->team->remain);
	add_msg_to_player(p, str, ret, 1);
}
