#include <string.h>
#include "serveur.h"

extern int	g_log;

void	pre_action_avance(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	action_player_move(var, &dummy, dummy.facing);
	message_gfx_ppo(var, NULL, &dummy);
	if (g_log & LOG_P)
		log_simple_message(p, LOG_P, "avance");
}

void	pre_action_droite(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing + 1 == 4) ? 0 : dummy.facing + 1;
	message_gfx_ppo(var, NULL, &dummy);
	if (g_log & LOG_P)
		log_simple_message(p, LOG_P, "droite");
}

void	pre_action_gauche(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing - 1 < 0) ? 3 : dummy.facing - 1;
	message_gfx_ppo(var, NULL, &dummy);
	if (g_log & LOG_P)
		log_simple_message(p, LOG_P, "gauche");
}

void	pre_action_expulse(t_zappy *var, t_player *p, t_aargs *args)
{
	if (!(args->pl = (int *)malloc(sizeof(int) * MAX_FD)))
		return (message_player_ko(p));
	bzero(args->pl, sizeof(int) * MAX_FD);
	message_gfx_pex(var, NULL, p);
	args->nb = command_expulse_count_player(var, p, args->pl);
	if (g_log & LOG_P)
		log_simple_message(p, LOG_P, "expulse");
}

void	pre_action_inventaire(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)args;
	message_gfx_pin(var, NULL, p);
	if (g_log & LOG_P)
		log_simple_message(p, LOG_P, "inventaire");
}
