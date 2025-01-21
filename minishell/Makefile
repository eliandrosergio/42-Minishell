# **************************************************************************** #
#                                                                              #
#                                                        :::      ::::::::     #
#   Makefile                                           :+:      :+:    :+:     #
#                                                    +:+ +:+         +:+       #
#   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+          #
#                                                +#+#+#+#+#+   +#+             #
#   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#               #
#   Updated: 2025/01/10 15:13:02 by efaustin         ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -rf

SRCS 		= srcs/main.c \
       srcs/shell.c \
       srcs/built_in/cd.c \
       srcs/built_in/echo.c \
       srcs/built_in/env.c \
       srcs/built_in/exit.c \
       srcs/built_in/export.c \
       srcs/built_in/pwd.c \
       srcs/built_in/unset.c \
       srcs/exec/check_path.c \
       srcs/exec/exec_cmd_line.c \
       srcs/exec/execute.c \
       srcs/exec/handle_separator.c \
       srcs/exec/process_io.c \
       srcs/exec/var_arg_exp.c \
       srcs/exec/var_file_exp.c \
       srcs/exec/var_arg_exp_utils.c \
       srcs/exec/var_name_exp.c \
       srcs/exec/variable_expansion.c \
       srcs/lexer/lexer.c \
       srcs/lexer/handle_env/env_checks.c \
       srcs/lexer/handle_env/env_flags.c \
       srcs/lexer/handle_env/env_home.c \
       srcs/lexer/handle_env/env_offset.c \
       srcs/lexer/handle_env/env_offset2.c \
       srcs/lexer/handle_env/env_strcat.c \
       srcs/lexer/handle_env/handle_env.c \
       srcs/lexer/input/escape_characters.c \
       srcs/lexer/input/input_to_literal_input.c \
       srcs/lexer/input/trim_input.c \
       srcs/lexer/tokens/interpreted_tokens_flags.c \
       srcs/lexer/tokens/literal_input_to_literal_tokens.c \
       srcs/lexer/tokens/literal_tokens_flags.c \
       srcs/lexer/tokens/literal_tokens_to_interpreted_tokens.c \
       srcs/parser/parser.c \
       srcs/utils/array_utils.c \
       srcs/utils/command_utils.c \
       srcs/utils/cd_dir_utils.c \
       srcs/utils/cd_env_utils.c \
       srcs/utils/cd_path_utils.c \
       srcs/utils/cd_path_utils2.c \
       srcs/utils/cd_path_utils3.c \
       srcs/utils/cd_utils.c \
       srcs/utils/cd_utils2.c \
       srcs/utils/env_utils.c \
       srcs/utils/error_utils.c \
       srcs/utils/exec_utils.c \
       srcs/utils/exit_utils.c \
       srcs/utils/export_utils.c \
       srcs/utils/ft_atoi.c \
       srcs/utils/ft_itoa_base.c \
       srcs/utils/input_to_literal_tokens_utils.c \
       srcs/utils/literal_tokens_to_interpreted_tokens_utils.c \
       srcs/utils/list_utils.c \
       srcs/utils/list_utils2.c \
       srcs/utils/path_utils.c \
       srcs/utils/parse_utils.c \
       srcs/utils/push_pop_env.c \
       srcs/utils/shell_utils.c \
       srcs/utils/signal_utils.c \
       srcs/utils/sort.c \
       srcs/utils/utils1.c \
       srcs/utils/utils2.c \
       srcs/utils/var_arg_utils.c \
       srcs/utils/var_name_utils.c

OBJS		= $(SRCS:.c=.o)

INCLUDES 	= -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
