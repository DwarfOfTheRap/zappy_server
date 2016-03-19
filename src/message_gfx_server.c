#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_msz(t_zappy *var, t_player *gfx)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "msz %d %d", var->board_size[1], var->board_size[0]);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_bct(t_zappy *var, t_player *gfx, int pos[2])
{
	int		ret;
	int		*square;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	square = var->board[pos[0]][pos[1]];
	ret = sprintf(str, "bct %d %d %d %d %d %d %d %d %d", pos[1], pos[0],
		square[0], square[1], square[2], square[3], square[4], square[5],
		square[6]);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_mct(t_zappy *var, t_player *gfx, int *square)
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
			if (!bypass && var->gfx_client[i]->snd.full)
				break ;
			++(*square);
		}
		pos[1] = -1;
	}
	*square = -1;
}

void	message_gfx_tna(t_zappy *var, t_player *gfx)
{
	int		i;
	char	str[64];
	char	*str_name;

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	i = 0;
	stpncpy(str, "tna ", 4);
	str_name = str + 4;
	while (i < var->nb_team - 1)
	{
		stpncpy(str_name, var->teams[i].name, 33);
		if (gfx)
			add_msg_to_player(gfx, str, 0, 1);
		else
			add_msg_to_gfx(var, str, 0, 1);
		++i;
	}
}

void	message_gfx_sgt(t_zappy *var, t_player *gfx)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "sgt %d", var->tick);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}
