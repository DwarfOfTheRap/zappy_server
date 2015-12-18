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
	src/exit.c \
	src/init.c \
	src/read_arguments.c \
	src/serveur.c \
	src/usage.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	cd test && cmake . && make && make test

.PHONY: all clean fclean re test
