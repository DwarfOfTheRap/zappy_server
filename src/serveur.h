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
# define MAX_TICK	300
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

/*
** log level
*/
# define LOG_W		1
# define LOG_E		2
# define LOG_I		4
# define LOG_C		8
# define LOG_A		16
# define LOG_P		32

# define ABS(x)		(x < 0 ? -x : x)

# include "linked_lists.h"
# include "structs.h"

enum		e_action {AVANCE, DROITE, GAUCHE, VOIR, INVENTAIRE, PREND, POSE,
	EXPULSE, BROADCAST, INCANTATION, FORK, CONNECT_NBR};

/*
** src/action_gfx.c
*/
void		action_gfx_mct(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/action_player.c
*/
void		action_player_move(t_zappy *var, t_player *p, int dir);
void		action_player_avance(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_droite(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_gauche(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_expulse(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/action_player_2.c
*/
void		action_player_voir(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_prend(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_pose(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/action_player_3.c
*/
void		action_player_incantation(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_fork(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_connect_nbr(t_zappy *var, t_player *p, t_aargs *args);
void		action_player_inventaire(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/action_player_broadcast.c
*/
void		action_player_broadcast(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/action_queue.c
*/
void		process_actions(t_zappy *var);
int			action_add(t_action *action, t_zappy *var);
t_action	*action_create(t_aargs *arg, void (*f)(t_zappy*, t_player*,
				t_aargs*), t_player *player, long long time);
void		action_add_wrapper(t_zappy *var, t_player *p, t_aargs *args,
				int act);

/*
** src/action_queue_2.c
*/
void		action_player_clear(t_player *player, t_zappy *var);
t_action	*get_first_action(t_lst_head *list);
t_action	*get_last_action(t_lst_head *list);

/*
** src/action_queue_3.c
*/
int			count_player_actions(t_player *p, t_zappy *var);
t_action	*find_player_first_action(t_player *p, t_zappy *var);
t_action	*find_player_last_action(t_player *p, t_zappy *var);
void		reset_players_pending_action_count(t_zappy *var);

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
void		action_free(void *action);

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
void		command_avance(t_zappy *var, t_player *p, char *args);
void		command_droite(t_zappy *var, t_player *p, char *args);
void		command_gauche(t_zappy *var, t_player *p, char *args);
void		command_voir(t_zappy *var, t_player *p, char *args);
void		command_inventaire(t_zappy *var, t_player *p, char *args);

/*
** src/commands_player_2.c
*/
void		command_prend(t_zappy *var, t_player *p, char *args);
void		command_pose(t_zappy *var, t_player *p, char *args);
void		command_broadcast(t_zappy *var, t_player *p, char *args);
void		command_connect_nbr(t_zappy *var, t_player *p, char *args);

/*
** src/commands_player_3.c
*/
void		command_fork(t_zappy *var, t_player *p, char *args);
int			command_incantation_can_incant(t_zappy *var, t_player *p,
				int nb_player);
int			command_incantation_count_player(t_zappy *var, t_player *p,
				int *pl);
void		command_incantation_notification(t_zappy *var, t_player *p,
				t_aargs *args);
void		command_incantation(t_zappy *var, t_player *p, char *args);

/*
** src/commands_player_4.c
*/
void		command_expulse_send_to_gfx(t_zappy *var, t_player *p, t_player *p2,
				t_action *a);
int			command_expulse_count_player(t_zappy *var, t_player *p, int *pl);
void		command_expulse(t_zappy *var, t_player *p, char *args);

/*
** src/connexion.c
*/
int			close_client(t_zappy *var, t_server *serv, int fd);
void		client_error(t_player *p, char *str);
void		player_hatched(t_player *p, t_zappy *var);
void		init_client(t_zappy *var, t_player *p);
void		affect_team(t_zappy *var, t_player *p, char *str, size_t len);

/*
** src/connexion_2.c
*/
void		init_gfx(t_zappy *var, t_player *p);

/*
** src/do_accept.c
*/
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
** src/eggs.c
*/
void		egg_set_rotten_time(t_egg *egg, t_zappy *var);
void		check_eggs(t_zappy *var);
t_egg		*egg_add_wrapper(t_zappy *var, t_player *p);

/*
** src/egg_utils.c
*/
t_egg		*get_first_egg(t_lst_head *list);
t_egg		*get_last_egg(t_lst_head *list);
int			egg_add(t_egg *egg, t_zappy *var);
t_egg		*egg_create(t_player *p, t_zappy *var, long long time);

/*
** src/end_of_game.c
*/
void		check_if_team_win(t_zappy *var, t_server *serv);

/*
** src/exit.c
*/
void		exit_arg_error(int error, t_arguments *args);

/*
** src/health.c
*/
void		check_players_life(t_zappy *var);
void		player_spawn(t_player *p, t_zappy *var, int *coord);
void		player_die(t_zappy *var, t_player *p);
void		player_eat(t_player *p, t_zappy *var);
void		player_vomit(t_player *p, t_zappy *var);

/*
** src/health_2.c
*/
int			get_food_number(t_player *p, t_zappy *var);

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
void		main_loop(t_zappy *var, t_server *serv);

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
void		message_unknown_command(t_player *p, char *str);
void		message_command_format_error(t_player *p, char *str, char *args);
void		message_unsupported_command(t_player *p, char *str, char *args);
void		message_unauthorised_command(t_player *p, char *str, char *args);

/*
** src/message_gfx_egg.c
*/
void		message_gfx_ebo(t_zappy *var, t_egg *egg);
void		message_gfx_edi(t_zappy *var, t_egg *egg);
void		message_gfx_eht(t_zappy *var, t_egg *egg);
void		message_gfx_enw(t_zappy *var, t_egg *egg);

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
void		message_gfx_pic(t_zappy *var, t_player *p, int *pl);
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
void		message_gfx_mct(t_zappy *var, int *square);
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
** src/message_player.c
*/
void		message_player_ko(t_player *p);
void		message_player_ok(t_player *p);
void		message_player_separator(t_player *p, int sep);
void		message_player_voir_square_sub(t_zappy *var, t_player *p,
				int square[2]);
void		message_player_voir_square(t_zappy *var, t_player *p,
				int square[2]);

/*
** src/message_player_2.c
*/
void		message_player_connect_nbr(t_player *p);
void		message_player_expulsed(t_player *pusher, t_player *pushed);
void		message_player_incantation_end(t_player *p);
void		message_player_incantation_start(t_player *p);
void		message_player_message(t_player *p, int square, char *msg);

/*
** src/message_player_3.c
*/
void		message_player_mort(t_player *p);

/*
** src/pre_action.c
*/
void		pre_action_avance(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_droite(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_gauche(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_expulse(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_inventaire(t_zappy *var, t_player *p, t_aargs *args);

/*
** src/pre_action_2.c
*/
void		pre_action_prend(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_pose(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_broadcast(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_fork(t_zappy *var, t_player *p, t_aargs *args);
void		pre_action_incantation(t_zappy *var, t_player *p, t_aargs *args);

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
** src/read_arguments_2.c
*/
int			get_opt_verbose(t_main_arg const m_arg, int *i);

/*
** src/ressources_management.c
*/
void		add_ressource_on_random_square(t_zappy *var, int res);
void		add_ressource(t_zappy *var, int res, int nb);
void		init_ressources(t_zappy *var);
void		dispatch_incantation_ressources(t_zappy *var, t_player *p,
				const int *res);
void		drop_ressource_on_death(t_zappy *var, t_player *p);

/*
** src/time.c
*/
void		update_queue(int old_tick, t_zappy *var);
void		update_eggs(int old_tick, t_zappy *var);
void		update_player_timeofdeath(t_player *p, int old_tick, t_zappy *var);
void		zappy_update_tick(int tick, t_zappy *var);

/*
** src/time_compute.c
*/
long long	compute_new_time(long long trigger, int old_tick, t_zappy *var);
void		compute_action_new_time(t_action *action, int old_tick,
				t_zappy *var);
void		compute_egg_new_time(t_egg *egg, int old_tick, t_zappy *var);
void		compute_death_new_time(t_player *p, int old_tick, t_zappy *var);

/*
** src/tstmp_calcs.c
*/
int			time_compare(long long time1, long long time2);
t_tstmp		time_long_create(long long ms);
long long	time_generate(int ref, long long start, t_zappy *var);
long long	time_long(t_tstmp time);
void		time_add(t_tstmp *time1, t_tstmp *time2);

/*
** src/tstmp_calcs_2.c
*/
long long	time_elapsed(t_tstmp time1, t_tstmp time2);

/*
** src/tools
*/
char		*strjoin(char *str1, char *str2);
void		strdel(char **str);
int			same_square(int *s1, int *s2);

/*
** src/usage.c
*/
void		usage(void);

#endif
