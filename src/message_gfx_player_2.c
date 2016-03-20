#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_pbc(t_zappy *var, t_player *gfx, t_player *p, char *msg)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pbc %d ", p->unique_id);
	if (gfx)
	{
		add_msg_to_player(gfx, str, ret, 0);
		add_msg_to_player(gfx, msg, 0, 1);
	}
	else
	{
		add_msg_to_gfx(var, str, ret, 0);
		add_msg_to_gfx(var, msg, 0, 1);
	}
}

void	message_gfx_pie(t_zappy *var, t_player *gfx, t_player *p, int success)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pie %d %d %d", p->coord[1], p->coord[0], success);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_pfk(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pfk %d", p->unique_id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

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

void	message_gfx_pdr(t_zappy *var, t_player *gfx, t_player *p, int res_id)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pdr %d %d", p->unique_id, res_id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}
