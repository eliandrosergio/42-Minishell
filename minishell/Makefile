NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= src/main.c src/prompt.c src/executor.c src/parser.c src/command_completion.c
OBJ		= $(SRC:.c=.o)

INC		= -Iinc
LIBS	= -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
