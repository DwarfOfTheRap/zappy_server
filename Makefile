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
	src/connexion.c \
	src/commands.c \
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
	src/message_2.c \
	src/read_arguments.c \
	src/ressources_management.c \
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
