#include <stdio.h>
#include "server.h"

void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team> "
		"[<team>] [<team>] ... -c <nb> -t <t>\n");
	printf("-p numero de port. \e[0;32m%d\e[0m <= port <= \e[0;32m%d\e[0m\n",
		MIN_PORT, MAX_PORT);
	printf("-x largeur du Monde. \e[0;32m%d\e[0m <= largeur <= "
		"\e[0;32m%d\e[0m\n", MIN_MAP, MAX_MAP);
	printf("-y hauteur du Monde. \e[0;32m%d\e[0m <= hauteur <= "
		"\e[0;32m%d\e[0m\n", MIN_MAP, MAX_MAP);
	printf("-n nom\\ equipe\\ 1 nom\\ \\ equipe\\ 2 ...\n");
	printf("-c nombre de client autorises au commencement du jeu. "
		"\e[0;32m%d\e[0m <= nombre de client <= \e[0;32m%d\e[0m\n", MIN_CLIENT,
		MAX_FD - 4);
	printf("-t diviseur de l'unite de temps (plus t est grand, plus le "
		"jeu va vite). \e[0;32m%d\e[0m <= tick <= \e[0;32m%d\e[0m\n", MIN_TICK,
		MAX_TICK);
}
