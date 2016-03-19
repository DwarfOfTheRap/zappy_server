#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_seg(t_zappy *var, t_team *team)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "seg %s", team->name);
	add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_smg(t_zappy *var, char *msg)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	add_msg_to_gfx(var, "smg ", 4, 0);
	add_msg_to_gfx(var, msg, 0, 1);
}

void	message_gfx_suc(t_zappy *var)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	add_msg_to_gfx(var, "suc", 3, 1);
}

void	message_gfx_sbp(t_zappy *var)
{
	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	add_msg_to_gfx(var, "sbp", 3, 1);
}
