#include "serveur.h"

void	init_gfx_sub(t_zappy *var)
{
	long	i;

	i = -1;
	message_gfx_msz(var);
	message_gfx_sgt(var);
	message_gfx_mct(var, &i);
	message_gfx_tna(var);
	i = 3;
	while (i++ < *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT)
			message_gfx_ppo(var, &var->players[i]);
	}
	// need to iter on the eggs
}

void	init_gfx(t_zappy *var, t_player *p)
{
	if (p->team->remain)
	{
		p->status = FD_GFX;
		--p->team->remain;
		var->gfx_client = p;
		// save the current time to reverbate it on action queue
		init_gfx_sub(var);
		// iter on action queue to update tmstmp
	}
	else
		p->status = FD_CLOSE;
}
