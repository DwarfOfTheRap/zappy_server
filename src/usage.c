#include <stdio.h>
#include "serveur.h"

void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team> "
		"[<team>] [<team>] ... -c <nb> -t <t>\n");
	printf("-p numero de port. \033[0;32m%d\033[0m <= port <= "
		"\033[0;32m%d\033[0m\n", MIN_PORT, MAX_PORT);
	printf("-x largeur du Monde. \033[0;32m%d\033[0m <= largeur <= "
		"\033[0;32m%d\033[0m\n", MIN_MAP, MAX_MAP);
	printf("-y hauteur du Monde. \033[0;32m%d\033[0m <= hauteur <= "
		"\033[0;32m%d\033[0m\n", MIN_MAP, MAX_MAP);
	printf("-n nom\\ equipe\\ 1 nom\\ \\ equipe\\ 2 ...\n");
	printf("-c nombre de client autorises au commencement du jeu. "
		"\033[0;32m%d\033[0m <= nombre de client <= \033[0;32m%d\033[0m\n",
		MIN_CLIENT, MAX_FD - 4);
	printf("-t diviseur de l'unite de temps (plus t est grand, plus le "
		"jeu va vite). \033[0;32m%d\033[0m <= tick <= \033[0;32m%d\033[0m\n",
		MIN_TICK, MAX_TICK);
}
