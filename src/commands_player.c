#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;
	t_player	dummy;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, AVANCE);
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	action_player_move(var, &dummy, dummy.facing);
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> avance\n", p->id);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;
	t_player	dummy;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, DROITE);
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing + 1 == 4) ? 0 : dummy.facing + 1;
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> droite\n", p->id);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;
	t_player	dummy;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, GAUCHE);
	memcpy(&dummy, p, sizeof(t_player) - sizeof(t_rcv_buf) - sizeof(t_snd_buf));
	dummy.facing = (dummy.facing - 1 < 0) ? 3 : dummy.facing - 1;
	message_gfx_ppo(var, &dummy);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> gauche\n", p->id);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, VOIR);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> voir\n", p->id);
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, INVENTAIRE);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> inventaire\n", p->id);
}
