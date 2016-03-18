# zappy_server
[![Build Status](https://travis-ci.org/DwarfOfTheRap/zappy_server.svg?branch=master)](https://travis-ci.org/DwarfOfTheRap/zappy_server)

42 school project zappy - server

## Trello board
Here is the [public link](https://trello.com/b/SAMysnab) to our trello, cause we planned our work on trello.

## How to

### Get and test
```bash
git clone https://github.com/DwarfOfTheRap/zappy_server.git
cd zappy_server
make
make test
```

Please note that the libcheck is a requirement for if you want to run the test.

### Run the server
```bash
./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t> [-v weicap]
-p port number. 1024 <= port <= 65535
-x world width. 10 <= largeur <= 50
-y world height. 10 <= hauteur <= 50
-n team\ name\ 1 team\ \ name\ 2 ...
-c number of client at game start. 1 <= nombre de client <= 252
-t time divisor (the higher it is, the fastest the game will run). 1 <= tick <= 500
-v weicap. choose the letter corresponding to what you whish to log : Warning Error Info, Commands, Action, Pre-action
```
