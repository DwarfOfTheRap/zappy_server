#include "serveur.h"

void	action_gfx_mct(t_zappy *var, t_player *p, t_aargs *args)
{
	t_action	*new;
	long long	time;

	(void)p;
	message_gfx_mct(var, &args->nb);
	if (args->nb != -1)
	{
		time = var->start_time;
		time++;
		new = action_create(args, &action_gfx_mct, NULL, time);
		if (!action_add(new, var))
			action_free(new);
	}
}
