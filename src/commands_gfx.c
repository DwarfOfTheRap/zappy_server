#include <string.h>
#include "serveur.h"

extern int	g_log;

void	command_msz(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_msz(var, p);
	if (g_log & LOG_C)
		log_gfx("msz");
}

void	command_bct(t_zappy *var, t_player *p, char *arg)
{
	char	*end_arg[2];
	int		pos[2];

	(void)p;
	bzero(end_arg, sizeof(char *) * 2);
	pos[1] = (int)strtol(arg, &end_arg[1], 10);
	if (end_arg[1] == arg)
		return (message_gfx_sbp(var, p));
	pos[0] = (int)strtol(end_arg[1], &end_arg[0], 10);
	if (end_arg[0] == end_arg[1])
		return (message_gfx_sbp(var, p));
	if (pos[0] < 0 || var->board_size[0] <= pos[0] ||
			pos[1] < 0 || var->board_size[1] <= pos[1])
		return (message_gfx_sbp(var, p));
	message_gfx_bct(var, p, pos);
	if (g_log & LOG_C)
		log_gfx_str("bct", arg);
}

void	command_mct(t_zappy *var, t_player *p, char *arg)
{
	t_aargs		t;
	t_action	*new;
	t_tstmp		time[2];

	(void)p;
	(void)arg;
	bzero(&t, sizeof(t_aargs));
	message_gfx_mct(var, p, &t.nb);
	if (t.nb != -1)
	{
		time[0] = var->start_time;
		time[1] = var->start_time;
		time[1].tv_usec++;
		new = action_create(&t, &action_gfx_mct, NULL, time);
		action_add(new, var);
	}
	if (g_log & LOG_C)
		log_gfx("mct");
}

void	command_tna(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_tna(var, p);
	if (g_log & LOG_C)
		log_gfx("tna");
}

void	command_sgt(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_sgt(var, p);
	if (g_log & LOG_C)
		log_gfx("sgt");
}
