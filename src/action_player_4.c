#include "serveur.h"

void	action_player_send_message(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)var;
	add_msg_to_player(p, args->str, 0, 1);
}
