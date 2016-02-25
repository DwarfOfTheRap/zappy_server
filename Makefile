NAME := serveur
ifeq ($(CC),cc)
	CC := clang
endif
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I src
LDFLAGS :=
SRC := \
	src/check_arguments.c \
	src/cleanup.c \
	src/commands.c \
	src/commands_pre_gfx.c \
	src/commands_pre_gfx_2.c \
	src/connexion.c \
	src/do_accept.c \
	src/do_read.c \
	src/do_write.c \
	src/exit.c \
	src/init.c \
	src/linked_lists.c \
	src/linked_lists_2.c \
	src/linked_lists_3.c \
	src/main_loop.c \
	src/message.c \
	src/message_gfx_egg.c \
	src/message_gfx_player.c \
	src/message_gfx_player_2.c \
	src/message_gfx_player_3.c \
	src/message_gfx_server.c \
	src/message_gfx_server_2.c \
	src/read_arguments.c \
	src/serveur.c \
	src/tools.c \
	src/usage.c
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
