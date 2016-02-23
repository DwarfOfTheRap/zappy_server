#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	command_gfx_msz(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	ret = sprintf(str, "msz %d %d", var->board_size[1], var->board_size[0]);
	add_msg_to_player(p, str, ret);
}

void	command_gfx_bct(t_zappy *var, t_player *p, int pos[2])
{
	int		ret;
	int		*square;
	char	str[64];

	square = var->board[pos[0]][pos[1]];
	ret = sprintf(str, "bct %d %d %d %d %d %d %d %d %d", pos[1], pos[0],
		square[0], square[1], square[2], square[3], square[4], square[5],
		square[6]);
	add_msg_to_player(p, str, ret);
}

void	command_gfx_mct(t_zappy *var, t_player *p, int square)
{
	int		pos[2];

	pos[0] = square / var->board_size[1];
	pos[1] = square - var->board_size[1] * pos[0];
	while (pos[0] < var->board_size[0])
	{
		while (pos[1] < var->board_size[1])
		{
			command_gfx_bct(var, p, pos);
			if (p->snd.full)
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

void	command_gfx_tna(t_zappy *var, t_player *p)
{
	int		i;
	char	str[64];
	char	*str_name;

	i = 0;
	stpncpy(str, "tna ", 4);
	str_name = str + 4;
	while (i < var->nb_team - 1)
	{
		stpncpy(str_name, var->teams[i].name, 33);
		add_msg_to_player(p, str, 0);
		++i;
	}
}

void	command_gfx_pnw(t_zappy *var, t_player *p)
