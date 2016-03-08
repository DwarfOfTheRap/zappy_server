#include "serveur.h"

void	action_gfx_mct(t_zappy *var, t_player *p, char *args)
{
	t_action	*new;
	t_tstmp		time;
	long		square;

	(void)p;
	square = (long)args;
	message_gfx_mct(var, &square);
	if (square != -1)
	{
		time = *var->start_time;
		++time.tv_usec;
		new = action_create((char *)square, &action_gfx_mct, NULL, time);
	}
}
