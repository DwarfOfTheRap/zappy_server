#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_msz(t_zappy *var)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "msz %d %d", var->board_size[1], var->board_size[0]);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_bct(t_zappy *var, int pos[2])
{
	int		ret;
	int		*square;
	char	str[64];

	if (!var->gfx_client)
		return ;
	square = var->board[pos[0]][pos[1]];
	ret = sprintf(str, "bct %d %d %d %d %d %d %d %d %d", pos[1], pos[0],
		square[0], square[1], square[2], square[3], square[4], square[5],
		square[6]);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_mct(t_zappy *var, int square)
{
	int		pos[2];

	if (!var->gfx_client)
		return ;
	pos[0] = square / var->board_size[1];
	pos[1] = square - var->board_size[1] * pos[0];
	while (pos[0] < var->board_size[0])
	{
		while (pos[1] < var->board_size[1])
		{
			message_gfx_bct(var, pos);
			if (var->gfx_client->snd.full)
			{
				// we need to save one way or another the square to call this
				// function the next loop
				break ;
			}
			++square;
			++pos[1];
		}
		pos[1] = 0;
		++pos[0];
	}
}

void	message_gfx_tna(t_zappy *var)
{
	int		i;
	char	str[64];
	char	*str_name;

	if (!var->gfx_client)
		return ;
	i = 0;
	stpncpy(str, "tna ", 4);
	str_name = str + 4;
	while (i < var->nb_team - 1)
	{
		stpncpy(str_name, var->teams[i].name, 33);
		add_msg_to_player(var->gfx_client, str, 0, 1);
		++i;
	}
}

void	message_gfx_sgt(t_zappy *var)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "sgt %d", var->tick);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
