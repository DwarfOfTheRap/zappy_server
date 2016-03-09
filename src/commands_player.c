#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, AVANCE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> avance\n", p->id);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, DROITE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> droite\n", p->id);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, GAUCHE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> gauche\n", p->id);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, VOIR);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> voir\n", p->id);
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, INVENTAIRE);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> inventaire\n", p->id);
}
