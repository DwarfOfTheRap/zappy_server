#include <stdio.h>
#include "serveur.h"

const char	g_log_level[7][24];

void		log_simple_message(t_player *p, int type, char *str)
{
	int		t;

	t = 0;
	while (type)
	{
		type >>= 1;
		++t;
	}
	if (t < 1 || t > 6)
		return ;
	printf("[%s] p %d (%d) -> %s\n", g_log_level[t], p->id, p->unique_id, str);
}

void		log_message_str(t_player *p, int type, char *str, char *arg)
{
	int		t;

	t = 0;
	while (type)
	{
		type >>= 1;
		++t;
	}
	if (t < 1 || t > 6)
		return ;
	printf("[%s] p %d (%d) -> %s %s\n", g_log_level[t], p->id, p->unique_id,
			str, arg);
}

void		log_gfx(char *str)
{
	printf("[%s] %s\n", g_log_level[4], str);
}

void		log_gfx_str(char *str, char *arg)
{
	printf("[%s] %s %s\n", g_log_level[4], str, arg);
}

void		log_egg(int id, char *str)
{
	printf("[%s] Egg %d %s\n", g_log_level[3], id, str);
}
