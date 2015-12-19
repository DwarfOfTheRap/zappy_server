#include "serveur.h"

void	init_client(t_zappy *var, int client)
{
	bzero(&(var->players[client]), sizeof(t_player));
	var->players[client].id = client;
}

int		do_accept(t_zappy *var, t_server *serv)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;

	cslen = sizeof(csin);
	if ((cs = accept(serv->sock, (struct sockaddr *)&csin, &cslen)) < 0)
	{
		dprintf(2, "\033[0;31mError\033[0m: accept");
		return (1);
	}
	printf("New connection from %s\n", inet_ntoa(csin.sin_addr));
	init_client(var, cs);
	var->players[cs].status = FD_USE;
	var->players[cs].level = 1;
	if (cs > serv->fd_max)
		serv->fd_max += 1;
	return (0);
}
