#ifndef STRUCTS_H
# define STRUCTS_H
# include "linked_lists.h"

typedef struct timeval	t_tstmp;

typedef struct			s_rcv_buf
{
	char		buf[NB_RCV][RCV_SIZE + 1];
	u_short		read;
	u_short		write;
	char		full;
	char		*remain;
}						t_rcv_buf;

/*
** circular buffer but if overflow, has a linked list in order to avoid message
** loss; It's expect to be use (the linked list) when the gfx client ask for
** the map
*/
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
	char		name[TEAM_LEN + 1];
	int			remain;
	int			max_level;
	int			egg_slot_number;
}						t_team;

typedef struct			s_player
{
	int			id;
	int			inv[6];
	int			coord[2];
	int			pending_actions;
	t_team		*team;
	long long	timeofdeath;
	u_short		facing:2;
	u_short		status:3;
	u_short		level:4;
	t_rcv_buf	rcv;
	t_snd_buf	snd;
}						t_player;

typedef struct			s_egg
{
	int			id;
	int			coord[2];
	t_player	*mother;
	t_team		*team;
	long long	hatching_time;
}						t_egg;

typedef struct			s_zappy
{
	int			***board;
	int			board_size[2];
	int			team_size;
	int			tick;
	int			nb_team;
	int			*fd_max;
	char		game_won;
	t_team		*teams;
	t_lst_head	actions;
	t_lst_head	eggs;
	t_lst_head	eggs_hatched;
	int			egg_id_index;
	long long	start_time;
	t_player	players[MAX_FD];
	t_player	*gfx_client;
}						t_zappy;

typedef struct			s_aargs
{
	int			nb;
	int			*pl;
	char		*str;
}						t_aargs;

typedef struct			s_action
{
	t_aargs		arg;
	void		(*run)(t_zappy *var, t_player *p, t_aargs *arg);
	void		(*pre)(t_zappy *var, t_player *p, t_aargs *arg);
	t_player	*player;
	long long	trigger_t;
}						t_action;

typedef struct			s_cmd
{
	char	cmd[16];
	u_short	status:15;
	u_short arg:1;
	void	(*run)(t_zappy *var, t_player *p, char *arg);
}						t_cmd;

typedef struct			s_action_d
{
	void	(*f)(t_zappy*, t_player*, t_aargs*);
	void	(*pre)(t_zappy*, t_player*, t_aargs*);
	int		rel_time;
}						t_action_d;

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
