NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c src/prompt.c src/executor.c src/parser.c
OBJ = $(SRC:.c=.o)

INC = -Iinc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all