#include <stdlib.h>
#include <string.h>
#include "serveur.h"

void	update_pos_pointer(t_snd_buf *buf)
{
	buf->write = (buf->write + 1 == NB_SND) ? 0 : buf->write + 1;
	buf->pos = buf->buf[buf->write];
	buf->full = (buf->write == buf->read) ? 1 : 0;
	if (!buf->full)
		*buf->pos = '\0';
}

void	add_msg_to_player_lst(t_player *p, const char *msg, size_t len, int cr)
{
	t_lst_elem		*new;

	if (!(new = (t_lst_elem *)malloc(sizeof(t_lst_elem))))
		return ;
	bzero(new, sizeof(t_lst_elem));
	if (!(new->content = malloc(len + 1)))
	{
		free(new);
		return ;
	}
	memcpy(new->content, msg, len);
	if (cr)
		((char *)new->content)[len - 1] = '\n';
	((char *)new->content)[len] = '\0';
	lst_pushback(&p->snd.lst, new);
}

void	add_msg_to_player(t_player *p, const char *msg, size_t len, int cr)
{
	size_t	pos;
	size_t	cpy;
	size_t	avail;

	pos = 0;
	len = (len) ? len : strlen(msg);
	while (!p->snd.full && pos < len)
	{
		avail = SND_SIZE - (p->snd.pos - p->snd.buf[p->snd.write]);
		cpy = (avail >= len - pos) ? len - pos : avail;
		p->snd.pos = stpncpy(p->snd.pos, msg + pos, cpy);
		pos += cpy;
		if (p->snd.pos - SND_SIZE == p->snd.buf[p->snd.write])
			update_pos_pointer(&p->snd);
	}
	if (p->snd.full && len - pos + cr > 0)
		add_msg_to_player_lst(p, msg + pos, len - pos + cr, cr);
	else if (cr)
	{
		memcpy(p->snd.pos, "\n", 2);
		if (p->snd.pos - SND_SIZE == p->snd.buf[p->snd.write])
			update_pos_pointer(&p->snd);
		else
			++p->snd.pos;
	}
}

void	clean_msg_queue(t_player *p)
{
	lst_delete(&p->snd.lst, free);
	if (p->rcv.remain)
	{
		free(p->rcv.remain);
		p->rcv.remain = NULL;
	}
	p->snd.buf[p->snd.write][0] = 0;
	p->snd.read = 0;
	p->snd.write = 0;
	p->snd.pos = p->snd.buf[p->snd.write];
}

char	*pop_msg(t_lst_head *head)
{
	char		*str;
	t_lst_elem	*elem;

	elem = lst_pop(head, 0);
	str = (char *)elem->content;
	free(elem);
	return (str);
}
