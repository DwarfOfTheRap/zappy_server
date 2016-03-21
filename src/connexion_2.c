#include <strings.h>
#include "serveur.h"

static void		init_gfx_eggs(t_zappy *var)
{
	t_lst_elem	*temp;

	temp = var->eggs.first;
	while (temp)
	{
		message_gfx_enw(var, temp->content);
		temp = temp->next;
	}
	temp = var->eggs_hatched.first;
	while (temp)
	{
		message_gfx_enw(var, temp->content);
		message_gfx_eht(var, temp->content);
		temp = temp->next;
	}
}

static void		init_gfx_sub(t_zappy *var)
{
	int			i;

	i = -1;
	message_gfx_msz(var);
	message_gfx_sgt(var);
	message_gfx_mct(var, &i);
	message_gfx_tna(var);
	i = 3;
	while (++i <= *var->fd_max)
	{
		if (var->players[i].status == FD_CLIENT)
			message_gfx_pnw(var, &var->players[i]);
	}
	init_gfx_eggs(var);
}

void			init_gfx(t_zappy *var, t_player *p)
{
	if (p->team->remain)
	{
		p->status = FD_GFX;
		--p->team->remain;
		var->gfx_client = p;
		init_gfx_sub(var);
	}
	else
	{
		p->status = FD_CLOSE;
		p->team = NULL;
	}
}
