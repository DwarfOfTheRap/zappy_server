#include "serveur.h"

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_ppo(var, p);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_ppo(var, p);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
	message_gfx_ppo(var, p);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	(void)args;
	// add player action to action queue
}
