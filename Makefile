NAME = philo

SRC = src/main.c src/check.c src/init.c src/time.c src/actions.c \

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re