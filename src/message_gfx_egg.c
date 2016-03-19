#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_enw(t_zappy *var, t_player *gfx, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->teams[var->nb_team - 1].remain != NB_GFX && egg))
		return ;
	ret = sprintf(str, "enw %d %d %d %d", egg->id, egg->mother->unique_id,
			egg->coord[1], egg->coord[0]);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_eht(t_zappy *var, t_player *gfx, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->teams[var->nb_team - 1].remain != NB_GFX && egg))
		return ;
	ret = sprintf(str, "eht %d", egg->id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_ebo(t_zappy *var, t_player *gfx, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->teams[var->nb_team - 1].remain != NB_GFX && egg))
		return ;
	ret = sprintf(str, "ebo %d", egg->id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_edi(t_zappy *var, t_player *gfx, t_egg *egg)
{
	int		ret;
	char	str[64];

	if (!(var->teams[var->nb_team - 1].remain != NB_GFX && egg))
		return ;
	ret = sprintf(str, "edi %d", egg->id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}
