#include <stdio.h>
#include <string.h>
#include "serveur.h"

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

static void		message_gfx_pic_sub(t_zappy *var, t_player *p, int *pl,
		char *str)
{
	int		i;
	int		ret;

	ret = strlen(str);
	add_msg_to_gfx(var, str, ret, 0);
	i = 3;
	while (i <= *(var->fd_max))
	{
		if (pl[i] && i != p->id)
		{
			ret = sprintf(str, " %d", var->players[i].unique_id);
			add_msg_to_gfx(var, str, ret, 0);
		}
		++i;
	}
	add_msg_to_gfx(var, "", 0, 1);
}

void	message_gfx_pic(t_zappy *var, t_player *gfx, t_player *p, int *pl)
{
	int		i;
	int		ret;
	char	str[64];

	if (var->teams[var->nb_team - 1].remain == NB_GFX)
		return ;
	ret = sprintf(str, "pic %d %d %d %d", p->coord[1], p->coord[0],
		p->level, p->unique_id);
	if (gfx)
	{
		add_msg_to_player(gfx, str, ret, 0);
		i = 3;
		while (i <= *(var->fd_max))
		{
			if (pl[i] && i != p->id)
			{
				ret = sprintf(str, " %d", var->players[i].unique_id);
				add_msg_to_player(gfx, str, ret, 0);
			}
			++i;
		}
		add_msg_to_player(gfx, "", 0, 1);
	}
	else
		message_gfx_pic_sub(var, p, pl, str);
}
