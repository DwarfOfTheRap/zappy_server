#include <string.h>
#include "serveur.h"

void	command_pre_msz(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_msz(var);
}

void	command_pre_bct(t_zappy *var, t_player *p, char *arg)
{
	char	*end_arg[2];
	int		pos[2];

	(void)p;
	bzero(end_arg, sizeof(void *) * 2);
	pos[1] = (int)strtol(arg, &end_arg[1], 10);
	if (end_arg[1] == arg)
		return (message_gfx_sbp(var));
	pos[0] = (int)strtol(end_arg[1], &end_arg[0], 10);
	if (end_arg[0] == end_arg[1])
		return (message_gfx_sbp(var));
	if (pos[0] < 0 || var->board_size[0] <= pos[0] ||
			pos[1] < 0 || var->board_size[1] <= pos[1])
		return (message_gfx_sbp(var));
	message_gfx_bct(var, pos);
}

void	command_pre_mct(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_mct(var, 0);
}

void	command_pre_tna(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_tna(var);
}

void	command_pre_sgt(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_sgt(var);
}
