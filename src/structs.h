#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct timeval	t_tstmp;

typedef struct			s_rcv_buf
{
	char		buf[NB_RCV][RCV_SIZE + 1];
	u_short		read;
	u_short		write;
	char		full;
	char		*remain;
}						t_rcv_buf;

typedef struct			s_snd_buf
{
	char		buf[NB_SND][SND_SIZE + 1];
	u_short		read;
	u_short		write;
	char		full;
	char		*pos;
	t_lst_head	lst;
}						t_snd_buf;

typedef struct			s_server
{
	int			sock;
	int			port;
	int			fd_max;
	int			fd_sel;
	fd_set		fd_read;
	fd_set		fd_write;
}						t_server;

typedef struct			s_team
{
	char		*name;
	int			remain;
}						t_team;

typedef struct			s_player
{
	int			id;
	int			inv[6];
	int			coord[2];
	int			fov;
	int			pending_actions;
	t_team		*team;
	t_tstmp		timeofdeath;
	u_short		facing:2;
	u_short		status:3;
	u_short		level:4;
	t_rcv_buf	rcv;
	t_snd_buf	snd;
}						t_player;

typedef struct			s_action
{
	char		*arg;
	char		*(*run)(t_player *);
	t_player	*player;
	t_tstmp		time;
}						t_action;

typedef struct			s_zappy
{
	int			***board;
	int			board_size[2];
	int			team_size;
	int			tick;
	int			nb_team;
	t_team		*teams;
	t_lst_head	actions;
	t_player	players[MAX_FD];
}						t_zappy;

typedef struct			s_cmd
{
	char	cmd[16];
	u_short	status:15;
	u_short arg:1;
	void	(*run)(t_zappy *var, t_player *p, char *arg);
}						t_cmd;

typedef struct			s_arguments
{
	int		port;
	int		width;
	int		height;
	int		nb_clients;
	int		tick;
	u_int	nb_team;
	t_team	*teams;
}						t_arguments;

typedef struct			s_main_arg
{
	int			ac;
	const char	**av;
}						t_main_arg;

#endif
