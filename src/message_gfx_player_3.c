#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	command_gfx_pgt(t_zappy *var, t_player *p, int res_id)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pgt %d %d", p->id, res_id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	command_gfx_pdi(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pdi %d", p->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
