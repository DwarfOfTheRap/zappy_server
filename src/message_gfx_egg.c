#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_enw(t_zappy *var, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->gfx_client && egg))
		return ;
	ret = sprintf(str, "enw %d %d %d %d", egg->id, egg->mother->id,
			egg->coord[1], egg->coord[0]);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_eht(t_zappy *var, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->gfx_client && egg))
		return ;
	ret = sprintf(str, "eht %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_ebo(t_zappy *var, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->gfx_client && egg))
		return ;
	ret = sprintf(str, "ebo %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	message_gfx_edi(t_zappy *var, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->gfx_client && egg))
		return ;
	ret = sprintf(str, "edi %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
