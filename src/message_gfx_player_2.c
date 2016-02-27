#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_pbc(t_zappy *var, t_player *p, char *msg)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pbc %d ", p->id);
	add_msg_to_player(var->gfx_client, str, ret, 0);
	add_msg_to_player(var->gfx_client, msg, 0, 1);
}

void	message_gfx_pic(t_zappy *var, t_player *p)
{
	int		i;
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pic %d %d %d %d", p->coord[1], p->coord[0], p->level,
		p->id);
	add_msg_to_player(var->gfx_client, str, ret, 0);
	i = 3;
	while (i <= *(var->fd_max))
	{
		if (var->players[i].status == FD_CLIENT && i != p->id &&
			var->players[i].level == p->level &&
			var->players[i].coord[0] == p->coord[0] &&
			var->players[i].coord[0] == p->coord[0])
		{
			ret = sprintf(str, " %d", i);
			add_msg_to_player(var->gfx_client, str, ret, 0);
		}
	}
	add_msg_to_player(var->gfx_client, "", 0, 1);
}

void	message_gfx_pie(t_zappy *var, t_player *p, int success)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pie %d %d %d", p->coord[1], p->coord[0], success);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_pfk(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pfk %d", p->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_pdr(t_zappy *var, t_player *p, int res_id)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pdr %d %d", p->id, res_id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
