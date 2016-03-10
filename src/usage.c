#include <stdio.h>
#include "serveur.h"

void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team> "
		"[<team>] [<team>] ... -c <nb> -t <t> [-v weica]\n");
	printf("-p numero de port. \033[0;32m%d\033[0m <= port <= "
		"\033[0;32m%d\033[0m\n", MIN_PORT, MAX_PORT);
	printf("-x largeur du Monde. \033[0;32m%d\033[0m <= largeur <= "
		"\033[0;32m%d\033[0m\n", MIN_MAP, MAX_MAP);
	printf("-y hauteur du Monde. \033[0;32m%d\033[0m <= hauteur <= "
		"\033[0;32m%d\033[0m\n", MIN_MAP, MAX_MAP);
	printf("-n nom\\ equipe\\ 1 nom\\ \\ equipe\\ 2 ...\n");
	printf("-c nombre de client autorises au commencement du jeu. "
		"\033[0;32m%d\033[0m <= nombre de client <= \033[0;32m%d / number of "
		"team\033[0m\n", MIN_CLIENT, MAX_FD - 4);
	printf("-t diviseur de l'unite de temps (plus t est grand, plus le "
		"jeu va vite). \033[0;32m%d\033[0m <= tick <= \033[0;32m%d\033[0m\n",
		MIN_TICK, MAX_TICK);
	printf("-v \033[0;33mw\033[0;31me\033[0;34mi\033[0;32mc\033[0;35ma\033[0m. "
		"\033[0;33mW\033[0marnings \033[0;31mE\033[0mrror \033[0;34mI\033[0mnfo"
		" \033[0;32mC\033[0mommands \033[0;35mA\033[0mction\n");
}
