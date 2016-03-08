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
# define FOOD_RATIO	100
# define RES_RATIO	100
# define TEAM_LEN	32

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
** buffer constants
*/
# define NB_RCV		5
# define RCV_SIZE	128
# define NB_SND		20
# define SND_SIZE	1024

# include "linked_lists.h"
# include "structs.h"

/*
** src/action_gfx.c
*/
void	action_gfx_mct(t_zappy *var, t_player *p, char *args);

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
** src/commands_gfx.o
*/
void		command_bct(t_zappy *var, t_player *p, char *arg);
void		command_mct(t_zappy *var, t_player *p, char *arg);
void		command_msz(t_zappy *var, t_player *p, char *arg);
void		command_sgt(t_zappy *var, t_player *p, char *arg);
void		command_tna(t_zappy *var, t_player *p, char *arg);

/*
** src/commands_gfx_2.o
*/
void		command_pin(t_zappy *var, t_player *p, char *arg);
void		command_plv(t_zappy *var, t_player *p, char *arg);
void		command_ppo(t_zappy *var, t_player *p, char *arg);
void		command_sst(t_zappy *var, t_player *p, char *arg);

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
int			rearrange_message_queue(t_player *p, size_t len, int buffer);
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
** src/message_gfx_player.c
*/
void		message_gfx_pex(t_zappy *var, t_player *p);
void		message_gfx_pin(t_zappy *var, t_player *p);
void		message_gfx_plv(t_zappy *var, t_player *p);
void		message_gfx_pnw(t_zappy *var, t_player *p);
void		message_gfx_ppo(t_zappy *var, t_player *p);

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
** src/message_gfx_server.c
*/
void		message_gfx_msz(t_zappy *var);
void		message_gfx_bct(t_zappy *var, int pos[2]);
void		message_gfx_mct(t_zappy *var, long *square);
void		message_gfx_sgt(t_zappy *var);
void		message_gfx_tna(t_zappy *var);

/*
** src/message_gfx_server_2.c
*/
void		message_gfx_sbp(t_zappy *var);
void		message_gfx_seg(t_zappy *var, t_team *team);
void		message_gfx_smg(t_zappy *var, char *msg);
void		message_gfx_suc(t_zappy *var);

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
** src/ressources_management.c
*/
void		add_ressource_on_random_square(t_zappy *var, int res);
void		add_ressource(t_zappy *var, int res, int nb);
void		init_ressources(t_zappy *var);
void		dispatch_incantation_ressources(t_zappy *var, t_player *p,
				const int *res);

/*
** src/tools
*/
char		*strjoin(char *str1, char *str2);
void		strdel(char **str);

/*
** src/usage.c
*/
void		usage(void);

/*
** src/tstmp_calcs.c
*/
int			time_compare(t_tstmp *time1, t_tstmp *time2);
t_tstmp		time_create(double seconds);
t_tstmp		time_generate(double ref, t_zappy *var);
double		time_double(t_tstmp *time);
void		time_add(t_tstmp *time1, t_tstmp *time2);

/*
** src/action_queue.c
*/
void		process_actions(t_tstmp *start, t_zappy *var);
int			action_add(t_action *action, t_zappy *var);
t_action	*action_create(char *arg, void (*f)(t_zappy*, t_player*, char*)
						, t_player *player, t_tstmp time);

#endif
