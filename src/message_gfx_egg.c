#include <stdio.h>
#include <string.h>
#include "serveur.h"

// we will need to replace the t_player egg with the appropriate struct for the
// egg once this one will be create
void	command_gfx_enw(t_zappy *var, t_player *p, t_player *egg)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "enw %d %d %d %d", egg->id, p->id, egg->coord[1],
		egg->coord[0]);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	command_gfx_eht(t_zappy *var, t_player *egg)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "enw %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	command_gfx_ebo(t_zappy *var, t_player *egg)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "ebo %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}

void	command_gfx_edi(t_zappy *var, t_player *egg)
{
	int		ret;
	char	str[64];

	if (!var->gfx_client)
		return ;
	ret = sprintf(str, "edi %d", egg->id);
	add_msg_to_player(var->gfx_client, str, ret, 1);
}
