#include <string.h>
#include "serveur.h"

extern int	g_log;

void	command_sst(t_zappy *var, t_player *p, char *arg)
{
	int		tick;
	char	*end;

	(void)p;
	tick = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var, p));
	if (tick < MIN_TICK || MAX_TICK < tick)
		return (message_gfx_sbp(var, p));
	zappy_update_tick(tick, var);
	message_gfx_sgt(var, NULL);
	if (g_log & LOG_C)
		log_gfx_str("sst", arg);
}

static int	get_player_from_unique_id(t_zappy *var, int unique_id)
{
	int		i;

	i = 4;
	while (i <= *var->fd_max && unique_id != var->players[i].unique_id)
		++i;
	if (i <= *var->fd_max && unique_id == var->players[i].unique_id)
		return (i);
	return (0);
}

void	command_ppo(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var, p));
	p_id = get_player_from_unique_id(var, p_id);
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var, p));
	message_gfx_ppo(var, p, &var->players[p_id]);
	if (g_log & LOG_C)
		log_gfx_str("ppo", arg);
}

void	command_plv(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var, p));
	p_id = get_player_from_unique_id(var, p_id);
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var, p));
	message_gfx_plv(var, p, &var->players[p_id]);
	if (g_log & LOG_C)
		log_gfx_str("plv", arg);
}

void	command_pin(t_zappy *var, t_player *p, char *arg)
{
	int		p_id;
	char	*end;

	(void)p;
	p_id = (int)strtol(arg, &end, 10);
	if (end == arg)
		return (message_gfx_sbp(var, p));
	p_id = get_player_from_unique_id(var, p_id);
	if (p_id <= 0 || MAX_FD < p_id || var->players[p_id].status != FD_CLIENT)
		return (message_gfx_sbp(var, p));
	message_gfx_pin(var, p, &var->players[p_id]);
	if (g_log & LOG_C)
		log_gfx_str("pin", arg);
}
