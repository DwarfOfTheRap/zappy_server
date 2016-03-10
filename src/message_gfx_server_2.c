#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_seg(t_zappy *var, t_team *team)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "seg %s", team->name);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_smg(t_zappy *var, char *msg)
{
	if (!var->gfx_client)
		return ;
	add_msg_to_player(var->gfx_client, "smg ", 4, 0);
	add_msg_to_player(var->gfx_client, msg, 0, 1);
}

void	message_gfx_suc(t_zappy *var)
{
	if (!var->gfx_client)
		return ;
	add_msg_to_player(var->gfx_client, "suc", 3, 1);
}

void	message_gfx_sbp(t_zappy *var)
{
	if (!var->gfx_client)
		return ;
	add_msg_to_player(var->gfx_client, "sbp", 3, 1);
}
