#include "serveur.h"

const int			g_move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

const char			g_ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame"};

const int			g_incant[7][7] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}};

const t_action_d	g_action[13] = {
	{&action_player_avance, &pre_action_avance, 7},
	{&action_player_droite, &pre_action_droite, 7},
	{&action_player_gauche, &pre_action_gauche, 7},
	{&action_player_voir, NULL, 7},
	{&action_player_inventaire, &pre_action_inventaire, 1},
	{&action_player_prend, &pre_action_prend, 7},
	{&action_player_pose, &pre_action_pose, 7},
	{&action_player_expulse, &pre_action_expulse, 7},
	{&action_player_broadcast, &pre_action_broadcast, 7},
	{&action_player_incantation, &pre_action_incantation, 300},
	{&action_player_fork, &pre_action_fork, 42},
	{&action_player_connect_nbr, NULL, 0},
	{&action_player_send_message, NULL, 0}};

int					g_log = 0;

int					g_continue = 1;
