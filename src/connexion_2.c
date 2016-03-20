#include <strings.h>
#include "serveur.h"

static void		init_gfx_eggs(t_zappy *var, t_player *gfx)
{
	t_lst_elem	*temp;

	temp = var->eggs.first;
	while (temp)
	{
		message_gfx_enw(var, gfx, temp->content);
		temp = temp->next;
	}
	temp = var->eggs_hatched.first;
	while (temp)
	{
		message_gfx_enw(var, gfx, temp->content);
		message_gfx_eht(var, gfx, temp->content);
		temp = temp->next;
	}
}

static void		init_gfx_sub(t_zappy *var, t_player *gfx)
{
	int			i;

	i = -1;
	message_gfx_msz(var, gfx);
	message_gfx_sgt(var, gfx);
	message_gfx_mct(var, gfx, &i);
	message_gfx_tna(var, gfx);
	i = 3;
	while (++i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT)
			message_gfx_pnw(var, gfx, &var->players[i]);
	}
	init_gfx_eggs(var, gfx);
}

void			init_gfx(t_zappy *var, t_player *p)
{
	int		i;

	if (p->team->remain)
	{
		p->status = FD_GFX;
		--p->team->remain;
		i = 0;
		while (i < NB_GFX && var->gfx_client[i])
			++i;
		var->gfx_client[i] = p;
		init_gfx_sub(var, p);
	}
	else
	{
		p->status = FD_CLOSE;
		p->team = NULL;
	}
}
