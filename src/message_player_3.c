#include "serveur.h"

void	message_player_mort(t_player *p)
{
	add_msg_to_player(p, "mort", 4, 1);
}
