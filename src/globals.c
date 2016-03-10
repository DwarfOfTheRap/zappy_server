#include "serveur.h"

const int			g_move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

const char			g_ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystam"};

const int			g_incant[7][7] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}};
	//  9, 8,10, 5, 6, 1

const t_action_d	g_action[12] = {
	{&action_player_avance, 7},
	{&action_player_droite, 7},
	{&action_player_gauche, 7},
	{&action_player_voir, 7},
	{&action_player_inventaire, 1},
	{&action_player_prend, 7},
	{&action_player_pose, 7},
	{&action_player_expulse, 7},
	{&action_player_broadcast, 7},
	{&action_player_incantation, 300},
	{&action_player_fork, 42},
	{&action_player_connect_nbr, 0}};

int					g_log = 0;
