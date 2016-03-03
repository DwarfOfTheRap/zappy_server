#ifndef SERVEUR_H
# define SERVEUR_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
** server constants
*/
# define MAX_FD		256
# define MIN_CLIENT	1
# define MIN_PORT	1024
# define MAX_PORT	65535
# define MIN_MAP	10
# define MAX_MAP	50
# define MIN_TICK	1
# define MAX_TICK	500

/*
** client status
*/
# define FD_FREE	0
# define FD_SERVER	1
# define FD_USED	2
# define FD_CLIENT	3
# define FD_GFX		4
# define FD_CLOSE	5

/*
** other define
*/
# define NB_RCV		5
# define RCV_SIZE	128
# define NB_SND		20
# define SND_SIZE	1024

# define ABS(x)		(x < 0 ? -x : x)

# include "linked_lists.h"
# include "structs.h"

/*
** src/action_player.c
*/
void	command_player_move(t_zappy *var, t_player *p, int dir);
void	command_player_avance(t_zappy *var, t_player *p, char *args);
void	command_player_droite(t_zappy *var, t_player *p, char *args);
void	command_player_gauche(t_zappy *var, t_player *p, char *args);
void	command_player_expulse(t_zappy *var, t_player *p, char *args);

/*
** src/action_player_2.c
*/
void	command_player_voir_sub(t_zappy *var, t_player *p, int k, int l);
void	command_player_voir(t_zappy *var, t_player *p, char *args);
void	command_player_inventaire(t_zappy *var, t_player *p, char *args);
void	command_player_prend(t_zappy *var, t_player *p, char *args);
void	command_player_pose(t_zappy *var, t_player *p, char *args);

/*
** src/action_player_3.c
*/
void	command_player_incantation(t_zappy *var, t_player *p, char *args);
void	command_player_fork(t_zappy *var, t_player *p, char args);

/*
** src/action_player_broadcast.c
*/
int		broadcast_get_distance(int ms[2], int s[2], int r[2], int i);
int		broadcast_get_direction(int ms[2], t_player *s, t_player *r);
int		broadcast_get_square(int ms[2], t_player *s, t_player *r);
void	command_player_broadcast(t_zappy *var, t_player *p, char *args);

/*
** src/check_arguments.c
*/
int			check_arguments(t_arguments *args, int error);

/*
** src/cleanup.c
*/
void		rm_teams(t_team **teams, int *nb_team);
void		rm_board(int ****board, int board_size[2], int i, int j);
void		cleanup_game(t_zappy *var, t_server *serv);

/*
** src/commands.c
*/
t_cmd const	*get_cmd_list(void);
int			command_match(t_cmd const cmd, char *str);
void		find_command(t_zappy *var, t_player *p, char *str, size_t len);

/*
** src/commands_gfx.c
*/
void		command_bct(t_zappy *var, t_player *p, char *arg);
void		command_mct(t_zappy *var, t_player *p, char *arg);
void		command_msz(t_zappy *var, t_player *p, char *arg);
void		command_sgt(t_zappy *var, t_player *p, char *arg);
void		command_tna(t_zappy *var, t_player *p, char *arg);

/*
** src/commands_gfx_2.c
*/
void		command_pin(t_zappy *var, t_player *p, char *arg);
void		command_plv(t_zappy *var, t_player *p, char *arg);
void		command_ppo(t_zappy *var, t_player *p, char *arg);
void		command_sst(t_zappy *var, t_player *p, char *arg);

/*
** src/commands_player.c
*/
void	command_avance(t_zappy *var, t_player *p, char *args);
void	command_droite(t_zappy *var, t_player *p, char *args);
void	command_gauche(t_zappy *var, t_player *p, char *args);
void	command_voir(t_zappy *var, t_player *p, char *args);
void	command_inventaire(t_zappy *var, t_player *p, char *args);

/*
** src/commands_player_2.c
*/
void	command_prend(t_zappy *var, t_player *p, char *args);
void	command_pose(t_zappy *var, t_player *p, char *args);
void	command_expulse(t_zappy *var, t_player *p, char *args);
void	command_broadcast(t_zappy *var, t_player *p, char *args);
void	command_incantation(t_zappy *var, t_player *p, char *args);

/*
** src/commands_player_3.c
*/
void	command_fork(t_zappy *var, t_player *p, char *args);
void	command_connect_nbr(t_zappy *var, t_player *p, char *args);

/*
** src/connexion.c
*/
int			close_client(t_zappy *var, t_server *serv, int fd);
void		client_error(t_player *p, char *str);
void		init_gfx(t_zappy *var, t_player *p);
void		init_client(t_zappy *var, t_player *p);
void		affect_team(t_zappy *var, t_player *p, char *str, size_t len);

/*
** src/do_accept.c
*/
void		accept_client(t_player *p, int client);
int			do_accept(t_zappy *var, t_server *serv);

/*
** src/do_read.c
*/
char		*process_input(t_zappy *var, t_player *p, char *str);
void		read_buffer(t_zappy *var, t_player *p);
int			do_read(t_zappy *var, t_server *serv, int fd);

/*
** src/do_write.c
*/
void		do_write(t_zappy *var, t_server *serv, int fd);

/*
** src/exit.c
*/
void		exit_arg_error(int error, t_arguments *args);

/*
** src/init.c
*/
int			init_board(int ****board, int board_size[2], int i, int j);
int			init_game_var(t_zappy *var, t_arguments *args);
int			init_server(t_zappy *var, t_server *serv, t_arguments *args);
int			init(t_zappy *var, t_server *serv, t_arguments *args);

/*
** src/main_loop.c
*/
void		pre_select(t_zappy *var, t_server *serv);
void		do_select(t_server *serv);
void		post_select(t_zappy *var, t_server *serv);
int			main_loop(t_zappy *var, t_server *serv);

/*
** src/message.c
*/
void		update_pos_pointer(t_snd_buf *buf);
void		add_msg_to_player_lst(t_player *p, const char *msg, size_t len,
				int cr);
void		add_msg_to_player(t_player *p, const char *msg, size_t len, int cr);
void		clean_msg_queue(t_player *p);
char		*pop_msg(t_lst_head *head);

/*
** src/message_2.c
*/
void		message_unknown_command(t_player *p);
void		message_command_format_error(t_player *p);
void		message_unsupported_command(t_player *p);
void		message_unauthorised_command(t_player *p);

/*
** src/message_gfx_egg.c
*/
void		message_gfx_ebo(t_zappy *var, t_player *egg);
void		message_gfx_edi(t_zappy *var, t_player *egg);
void		message_gfx_eht(t_zappy *var, t_player *egg);
void		message_gfx_enw(t_zappy *var, t_player *p, t_player *egg);

/*
** src/message_gfx_player_2.c
*/
void		message_gfx_pbc(t_zappy *var, t_player *p, char *msg);
void		message_gfx_pdr(t_zappy *var, t_player *p, int res_id);
void		message_gfx_pfk(t_zappy *var, t_player *p);
void		message_gfx_pic(t_zappy *var, t_player *p);
void		message_gfx_pie(t_zappy *var, t_player *p, int success);

/*
** src/message_gfx_player_3.c
*/
void		message_gfx_pdi(t_zappy *var, t_player *p);
void		message_gfx_pgt(t_zappy *var, t_player *p, int res_id);

/*
** src/message_gfx_player.c
*/
void		message_gfx_pex(t_zappy *var, t_player *p);
void		message_gfx_pin(t_zappy *var, t_player *p);
void		message_gfx_plv(t_zappy *var, t_player *p);
void		message_gfx_pnw(t_zappy *var, t_player *p);
void		message_gfx_ppo(t_zappy *var, t_player *p);

/*
** src/message_gfx_server_2.c
*/
void		message_gfx_sbp(t_zappy *var);
void		message_gfx_seg(t_zappy *var, t_team *team);
void		message_gfx_smg(t_zappy *var, char *msg);
void		message_gfx_suc(t_zappy *var);

/*
** src/message_gfx_server.c
*/
void		message_gfx_bct(t_zappy *var, int pos[2]);
void		message_gfx_mct(t_zappy *var, int square);
void		message_gfx_msz(t_zappy *var);
void		message_gfx_sgt(t_zappy *var);
void		message_gfx_tna(t_zappy *var);

/*
** src/message_player.o
*/
void		message_player_ko(t_player *p);
void		message_player_ok(t_player *p);
void		message_player_separator(t_player *p, int sep);
void		message_player_voir_square_sub(t_zappy *var, t_player *p,
				int square[2]);
void		message_player_voir_square(t_zappy *var, t_player *p, int square[2]);

/*
** src/message_player_2.o
*/
void		message_player_connect_nbr(t_player *p);
void		message_player_expulsed(t_player *pusher, t_player *pushed);
void		message_player_incantation_end(t_player *p);
void		message_player_incantation_start(t_player *p);
void		message_player_message(t_player *p, int square, char *msg);

/*
** src/message_player_3.o
*/
void		message_player_mort(t_player *p);

/*
** src/read_arguments.c
*/
int			z_error(char *str);
int			get_opt(const char *str);
int			get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args);
int			get_opt_int(t_main_arg const m_arg, int *i, int arg,
				t_arguments *args);
int			read_arguments(int ac, const char **av, t_arguments *args);

/*
** src/tools.c
*/
char		*strjoin(char *str1, char *str2);
void		strdel(char **str);

/*
** src/usage.c
*/
void		usage(void);

#endif
