#include <string.h>
#include "serveur.h"

void	update_pos_pointer(t_snd_buf *buf)
{
	buf->write = (buf->write + 1 == NB_RCV) ? 0 : buf->write + 1;
	buf->pos = buf->buf[buf->write];
	buf->full = (buf->write == buf->read) ? 1 : 0;
}

void	add_msg_to_player_lst(t_player *p, char *msg, size_t pos, size_t len)
{
	lst_pushback(&p->snd.lst, lst_create(msg + pos, len));
	((char *)(p->snd.lst.last->content))[len] = '\0';
}

void	add_msg_to_player(t_player *p, char *msg, size_t len)
{
	size_t	pos;
	size_t	cpy;
	size_t	avail;

	pos = 0;
	len = (len) ? len + 1 : strlen(msg) + 1;
	while (!p->snd.full && pos != len)
	{
		avail = SND_SIZE - (p->snd.pos - p->snd.buf[p->snd.write]);
		cpy = (avail >= len) ? len : avail;
		p->snd.pos = strncpy(p->snd.pos, msg + pos, cpy);
		pos += cpy;
		if (p->snd.pos - SND_SIZE == p->snd.buf[p->snd.write])
			update_pos_pointer(&p->snd);
		else
		{
			memcpy(p->snd.pos, "\n", 2);
			++p->snd.pos;
		}
	}
	if (pos != len)
		add_msg_to_player_lst(p, msg, cpy, len - cpy);
}

void	clean_msg_queue(t_player *p)
{
	lst_delete(&p->snd.lst, free);
}
