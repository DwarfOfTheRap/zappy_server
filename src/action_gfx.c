#include "serveur.h"

void	action_gfx_mct(t_zappy *var, t_player *p, t_aargs *args)
{
	t_action	*new;
	t_tstmp		time[2];

	(void)p;
	message_gfx_mct(var, &args->nb);
	if (args->nb != -1)
	{
		time[0] = var->start_time;
		time[1] = var->start_time;
		time[1].tv_usec++;
		new = action_create(args, &action_gfx_mct, NULL, time);
		action_add(new, var);
	}
}
