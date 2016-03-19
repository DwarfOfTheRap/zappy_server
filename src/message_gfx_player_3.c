#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_pgt(t_zappy *var, t_player *p, int res_id)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pgt %d %d", p->unique_id, res_id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_pdi(t_zappy *var, t_player *p)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "pdi %d", p->unique_id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
