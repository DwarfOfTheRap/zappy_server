#include <string.h>
#include <unistd.h>
#include "serveur.h"

void	do_write(t_zappy *var, t_server *serv, int fd)
{
	char		*str;
	t_player	*p;

	(void)serv;
	p = &var->players[fd];
	while (p->snd.full || p->snd.read != p->snd.write ||
			p->snd.buf[p->snd.write] != p->snd.pos)
	{
		write(fd, p->snd.buf[p->snd.read], strlen(p->snd.buf[p->snd.read]));
		p->snd.full = 0;
		if (p->snd.read == p->snd.write)
			update_pos_pointer(&p->snd);
		p->snd.read = (p->snd.read + 1 == NB_SND) ? 0 : p->snd.read + 1;
	}
	while (p->snd.lst.size)
	{
		str = pop_msg(&p->snd.lst);
		write(fd, str, strlen(str));
		free(str);
	}
	if (p->status == FD_CLOSE)
		close_client(var, serv, fd);
}
