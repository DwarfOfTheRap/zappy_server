#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	command_gfx_msz(t_zappy *var)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "msz %d %d", var->board_size[1], var->board_size[0]);
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_bct(t_zappy *var, int pos[2])
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
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_mct(t_zappy *var, int square)
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
			command_gfx_bct(var, pos);
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

void	command_gfx_tna(t_zappy *var)
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
		add_msg_to_player(var->gfx_client, str, 0);
		++i;
	}
}

void	command_gfx_pnw(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pnw %d %d %d %d %d %s", p->id, p->coord[1], p->coord[1],
		p->facing + 1, p->level, p->team->name);
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_ppo(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "ppo %d %d %d %d", p->id, p->coord[1], p->coord[1],
		p->facing + 1);
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_plv(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "plv %d %d", p->id, p->level);
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_pin(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pin %d %d %d %d %d %d %d %d %d %d", p->id, p->coord[1],
		p->coord[0], 0, p->inv[0], p->inv[1], p->inv[2], p->inv[3], p->inv[4], p->inv[5]);
	// need to replace the hard code 0 with life base on timestamp, waiting for
	// jability part for now
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_pex(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pex %d", p->id);
	add_msg_to_player(var->gfx_client, str, ret);
}

void	command_gfx_pbc(t_zappy *var, t_player *p, char *msg)
{
	(void)var;
	(void)p;
	(void)msg;
}
