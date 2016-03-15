#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	accept_client(t_player *p, int client)
{
	bzero(p, sizeof(t_player));
	bzero(&p->actions, sizeof(t_lst_head));
	p->id = client;
	p->snd.pos = p->snd.buf[0];
	p->status = FD_USED;
	add_msg_to_player(p, "BIENVENUE", 9, 1);
}

int		do_accept(t_zappy *var, t_server *serv)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;

	cslen = sizeof(csin);
	if ((cs = accept(serv->sock, (struct sockaddr *)&csin, &cslen)) < 0)
	{
		if (g_log & LOG_E)
			dprintf(2, "[\033[0;31mError\033[0m]: accept");
		return (1);
	}
	if (g_log & LOG_I)
		printf("[\033[0;34mINFO\033[0m] New connection from %s\n", inet_ntoa(csin.sin_addr));
	accept_client(&var->players[cs], cs);
	if (cs > serv->fd_max)
		serv->fd_max += 1;
	return (0);
}
