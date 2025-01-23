# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efaustin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#              #
#    Updated: 2025/01/22 16:27:00 by efaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= minishell
SRCS	= ./srcs/main.c							\
		./srcs/utils.c							\
		./srcs/built_in.c						\
		./srcs/built_in_2.c						\
		./srcs/init_shell.c						\
		./srcs/free_handler.c					\
		./srcs/parser/parser.c					\
		./srcs/parser/parser_utils.c			\
		./srcs/parser/parser_check_utils.c		\
		./srcs/parser/ft_parser_split.c			\
		./srcs/parser/redir/redir_utils.c		\
		./srcs/parser/redir/redir_handler.c		\
		./srcs/parser/redir/redir_fd_utils.c	\
		./srcs/parser/redir/heredoc_handler.c	\
		./srcs/exec/exec.c						\
		./srcs/exec/exec_bins.c					\
		./srcs/exec/exec_utils.c				\
		./srcs/env/env_utils.c					\
		./srcs/env/env_utils2.c					\
		./srcs/env/env_handle.c					\
		./srcs/expand/expand_sign.c				\
		./srcs/expand/expand_sign_utils.c		\

OBJS	= $(SRCS:.c=.o)
LIBFT	= libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -L./libft -lft

$(LIBFT):
	make -C libft
	make bonus -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
