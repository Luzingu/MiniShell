# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 15:58:50 by mcaquart          #+#    #+#              #
#    Updated: 2024/10/09 08:28:38 by mcaquart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	minishell
CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
LIBFT			= 	./libft
SRC				=	source/main.c							\
					source/redir_and_exec.c					\
					source/redir.c							\
					source/execute_builtin.c				\
					source/ft_verifying_line.c				\
					source/ft_verifying_argument.c			\
					source/execute_cmd.c					\
					source/increment_shell_level.c			\
					source/ft_free.c						\
					source/heredoc.c						\
					source/signal.c							\
					source/cmd_tab.c						\
					source/prev_sep.c						\
					source/ft_is_type.c						\
					source/return_str.c						\
					source/split_advenced.c					\
					source/split_advenced2.c				\
					source/is_separator.c					\
					source/get_separator.c					\
					source/get_tokens.c						\
					source/minipipe.c						\
					source/input.c							\
					source/str_dup_env.c					\
					source/numb_split.c						\
					source/ft_strisnum.c					\
					source/env_to_matrix.c					\
					source/add_envirenoment.c				\
					source/type_arg.c						\
					source/my_strndup.c						\
					source/builtins/ft_echo.c				\
					source/builtins/ft_cd.c					\
					source/builtins/ft_pwd.c				\
					source/builtins/ft_exit.c				\
					source/environment/get_env_value.c		\
					source/environment/expand_variables.c	\
					source/environment/ft_export.c			\
					source/environment/ft_unset.c			\
					source/environment/ft_env.c				\
					source/environment/ft_getenv.c			\
					source/environment/handle_unset.c		\
					source/environment/handle_export.c		\
					source/environment/sort_env.c
OBJ		= $(SRC:.c=.o)

MAKEFLAGS	+= -silent

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) -lreadline $(LIBFT)/libft.a -o $(NAME)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
