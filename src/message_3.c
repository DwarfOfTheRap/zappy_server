#include "serveur.h"

void	add_msg_to_gfx(t_zappy *var, char *msg, size_t len, int cr)
{
	int		i;

	i = 0;
	while (i < NB_GFX)
	{
		if (var->gfx_client[i])
			add_msg_to_player(var->gfx_client[i], msg, len, cr);
		++i;
	}
}
