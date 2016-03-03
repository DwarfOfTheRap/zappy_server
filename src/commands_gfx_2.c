#include <string.h>
#include "serveur.h"

void	command_sst(t_zappy *var, t_player *p, char *arg)
{
	int		tick;
	char	*end;

	(void)p;
	tick = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var));
	if (tick < MIN_TICK || MAX_TICK < tick)
		return (message_gfx_sbp(var));
	// trig game speed change
	message_gfx_sgt(var);
}

void	command_ppo(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	(void)p;
	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var));
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var));
	message_gfx_ppo(var, &var->players[p_id]);
}

void	command_plv(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	(void)p;
	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var));
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var));
	message_gfx_plv(var, &var->players[p_id]);
}

void	command_pin(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	(void)p;
	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var));
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var));
	message_gfx_pin(var, &var->players[p_id]);
}
