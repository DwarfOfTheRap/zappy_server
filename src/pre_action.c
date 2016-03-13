#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	pre_action_avance(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	action_player_move(var, &dummy, dummy.facing);
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> avance\n", p->id);
}

void	pre_action_droite(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing + 1 == 4) ? 0 : dummy.facing + 1;
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> droite\n", p->id);
}

void	pre_action_gauche(t_zappy *var, t_player *p, t_aargs *args)
{
	t_player	dummy;

	(void)args;
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing - 1 < 0) ? 3 : dummy.facing - 1;
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d ->gauche\n", p->id);
}

void	pre_action_expulse(t_zappy *var, t_player *p, t_aargs *args)
{
	if (!(args->pl = (int *)malloc(sizeof(int) * MAX_FD)))
		return (message_player_ko(p));
	bzero(args->pl, sizeof(int) * MAX_FD);
	message_gfx_pex(var, p);
	args->nb = command_expulse_count_player(var, p, args->pl);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> expulse\n", p->id);
}
