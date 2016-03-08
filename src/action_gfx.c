#include "serveur.h"

void	action_gfx_mct(t_zappy *var, t_player *p, char *args)
{
	long		square;

	(void)p;
	square = (long)args;
	message_gfx_mct(var, &square);
	if (square != -1)
	{
	}
}
