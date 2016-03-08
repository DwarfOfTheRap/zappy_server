#include "serveur.h"

extern t_action_d	g_action[9];

void				update_g_action(t_zappy *var)
{
	g_action[0].t = time_generate(7, var);
	g_action[1].t = g_action[0].t;
	g_action[2].t = g_action[0].t;
	g_action[3].t = g_action[0].t;
	g_action[4].t = time_generate(1, var);
	g_action[5].t = g_action[0].t;
	g_action[6].t = g_action[0].t;
	g_action[7].t = g_action[0].t;
	g_action[8].t = g_action[0].t;
	g_action[9].t = time_generate(300, var);
	g_action[10].t = time_generate(42, var);
}
