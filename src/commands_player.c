#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	if (!p->actions->size)
		pre_action_avance(var, p, NULL);
	action_add_wrapper(var, p, &t, AVANCE);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> avance\n", p->id);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	if (!p->actions->size)
		pre_action_droite(var, p, NULL);
	action_add_wrapper(var, p, &t, DROITE);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> droite\n", p->id);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	bzero(&t, sizeof(t_aargs));
	if (!p->actions->size)
		pre_action_gauche(var, p, NULL);
	action_add_wrapper(var, p, &t, GAUCHE);
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
