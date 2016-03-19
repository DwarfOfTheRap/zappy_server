#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_pgt(t_zappy *var, t_player *gfx, t_player *p, int res_id)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pgt %d %d", p->unique_id, res_id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_pdi(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pdi %d", p->unique_id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}
