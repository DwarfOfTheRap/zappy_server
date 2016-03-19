#include <stdio.h>
#include <string.h>
#include "serveur.h"

void		message_gfx_smg(t_zappy *var, t_player *gfx, char *msg)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	if (gfx)
	{
		add_msg_to_player(gfx, "smg ", 4, 0);
		add_msg_to_player(gfx, msg, 0, 1);
	}
	else
	{
		add_msg_to_gfx(var, "smg ", 4, 0);
		add_msg_to_gfx(var, msg, 0, 1);
	}
}

void		message_gfx_suc(t_zappy *var, t_player *gfx)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	if (gfx)
		add_msg_to_player(gfx, "suc", 3, 1);
	else
		add_msg_to_gfx(var, "suc", 3, 1);
}

void		message_gfx_sbp(t_zappy *var, t_player *gfx)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	if (gfx)
		add_msg_to_player(gfx, "sbp", 3, 1);
	else
		add_msg_to_gfx(var, "sbp", 3, 1);
}

static int	is_gfx_buffer_full(t_zappy *var, t_player *gfx)
{
	int			i;

	if (gfx)
		return (gfx->snd.full);
	i = 0;
	while (i < NB_GFX)
	{
		if (var->gfx_client[i] && var->gfx_client[i]->snd.full)
			return (1);
		++i;
	}
	return (0);
}

void		message_gfx_mct(t_zappy *var, t_player *gfx, int *square)
{
	int		i;
	int		pos[2];
	int		bypass;

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	i = 0;
	while (i < NB_GFX && !var->gfx_client[i])
		++i;
	bypass = (*square == -1) ? 1 : 0;
	*square = (*square == -1) ? 0 : *square;
	pos[0] = *square / var->board_size[1] - 1;
	pos[1] = *square - var->board_size[1] * (pos[0] + 1) - 1;
	while (++pos[0] < var->board_size[0])
	{
		while (++pos[1] < var->board_size[1])
		{
			message_gfx_bct(var, gfx, pos);
			if (!bypass && is_gfx_buffer_full(var, gfx))
				break ;
			++(*square);
		}
		pos[1] = -1;
	}
	*square = -1;
}
