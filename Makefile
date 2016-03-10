NAME := serveur
ifeq ($(CC),cc)
	CC := clang
endif
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I src
LDFLAGS :=
SRC := \
	src/action_gfx.c \
	src/action_player.c \
	src/action_player_2.c \
	src/action_player_3.c \
	src/action_player_broadcast.c \
	src/check_arguments.c \
	src/cleanup.c \
	src/commands.c \
	src/commands_gfx.c \
	src/commands_gfx_2.c \
	src/commands_player.c \
	src/commands_player_2.c \
	src/commands_player_3.c \
	src/connexion.c \
	src/connexion_2.c \
	src/do_accept.c \
	src/do_read.c \
	src/do_write.c \
	src/exit.c \
	src/globals.c \
	src/init.c \
	src/linked_lists.c \
	src/linked_lists_2.c \
	src/linked_lists_3.c \
	src/main_loop.c \
	src/message.c \
	src/message_2.c \
	src/message_gfx_egg.c \
	src/message_gfx_player.c \
	src/message_gfx_player_2.c \
	src/message_gfx_player_3.c \
	src/message_gfx_server.c \
	src/message_gfx_server_2.c \
	src/message_player.c \
	src/message_player_2.c \
	src/message_player_3.c \
	src/read_arguments.c \
	src/read_arguments_2.c \
	src/ressources_management.c \
	src/serveur.c \
	src/usage.c \
	src/tstmp_calcs.c \
	src/action_queue.c \
	src/action_queue_2.c \
	src/tools.c \
	src/usage.c \
	src/globals.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	cd test && cmake . && make && make test

.PHONY: all clean fclean re test
