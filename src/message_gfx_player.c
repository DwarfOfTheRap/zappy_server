#include <stdio.h>
#include <string.h>
#include "serveur.h"

void	message_gfx_pnw(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pnw %d %d %d %d %d %s", p->unique_id, p->coord[1],
		p->coord[0], p->facing + 1, p->level, p->team->name);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_ppo(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "ppo %d %d %d %d", p->unique_id, p->coord[1],
		p->coord[0], p->facing + 1);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_plv(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "plv %d %d", p->unique_id, p->level);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_pin(t_zappy *var, t_player *gfx, t_player *p)
{
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pin %d %d %d %d %d %d %d %d %d %d", p->unique_id,
		p->coord[1], p->coord[0], get_food_number(p, var), p->inv[0], p->inv[1],
		p->inv[2], p->inv[3], p->inv[4], p->inv[5]);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}

void	message_gfx_pex(t_zappy *var, t_player *gfx, t_player *p)
{
	int			ret;
	char		str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pex %d", p->unique_id);
	if (gfx)
		add_msg_to_player(gfx, str, ret, 1);
	else
		add_msg_to_gfx(var, str, ret, 1);
}
